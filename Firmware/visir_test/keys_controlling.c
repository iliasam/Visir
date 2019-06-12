/* Includes ------------------------------------------------------------------*/
#include "keys_controlling.h"
#include "stm32f4xx_gpio.h"
#include "power_controlling.h"
#include "main.h"
#include "string.h"
#include "mavlink_handling.h"
#include "hardware.h"
//#include "telescope_mode.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//Time in ms
#define KEY_HOLD_TIME            900

//Time in ms
#define KEY_PRESSED_TIME         50

//Time in ms
#define KEY_RELEASE_TIME         50

//Time in ms
#define KEYS_STARTUP_DELAY      500

#define KEY_POWER_CODE          1
#define KEY_MENU_CODE           2

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
key_item_t key_power;
key_item_t key_menu;

uint32_t keys_startup_timer = 0;
uint8_t keys_startup_lock_flag = 1;

extern volatile uint32_t ms_tick;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

void keys_init(void)
{
  key_power.gpio_name = BUTTON_1_GPIO;
  key_power.pin_name = BUTTON_1_PIN;
  keys_functons_init_hardware(&key_power);
  
  key_menu.gpio_name = BUTTON_2_GPIO;
  key_menu.pin_name = BUTTON_2_PIN;
  keys_functons_init_hardware(&key_menu);
  START_TIMER(keys_startup_timer, KEYS_STARTUP_DELAY);
}

void key_handling(void)
{
  keys_functons_update_key_state(&key_power);
  keys_functons_update_key_state(&key_menu);
  
  if (TIMER_ELAPSED(keys_startup_timer) == 0)
    return; //delay before startup
  else
  {
    if (keys_startup_lock_flag && (key_power.state == KEY_PRESSED))
      return;
    else
      keys_startup_lock_flag = 0;
  }
  
  //POWER
  if ((key_power.prev_state == KEY_PRESSED) && 
      (key_power.state == KEY_WAIT_FOR_RELEASE))
  {
    power_controlling_event();
    mavlink_send_key_event(KEY_POWER_CODE, 1);
    hardware_backlight_switch();
  }
  
  if ((key_power.prev_state == KEY_PRESSED) && 
      (key_power.state == KEY_HOLD))
  {
    power_controlling_event();
    mavlink_send_key_event(KEY_POWER_CODE, 2);
    //telescope_mode_switch_mode();
  }
  
  //MENU
  
  if ((key_menu.prev_state == KEY_PRESSED) && 
      (key_menu.state == KEY_WAIT_FOR_RELEASE))
  {
    power_controlling_event();
    mavlink_send_key_event(KEY_MENU_CODE, 1);
  }
  
  if ((key_menu.prev_state == KEY_PRESSED) && 
      (key_menu.state == KEY_HOLD))
  {
    power_controlling_event();
    mavlink_send_key_event(KEY_MENU_CODE, 2);
  }
}

//*****************************************************************************

// Initialize single key pin
void keys_functons_init_hardware(key_item_t* key_item)
{
  if (key_item == NULL)
    return;
  
  GPIO_InitTypeDef GPIO_InitStructure;
  
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Pin = key_item->pin_name;
  GPIO_Init(key_item->gpio_name, &GPIO_InitStructure);
  
  key_item->state = KEY_RELEASED;
}

void keys_functons_update_key_state(key_item_t* key_item)
{
  key_item->prev_state = key_item->state;
  
  if ((key_item->gpio_name->IDR & key_item->pin_name) != 0)
    key_item->current_state = 1;
  else
    key_item->current_state = 0;
  
  if ((key_item->state == KEY_RELEASED) && (key_item->current_state != 0))
  {
    //key presed now
    key_item->state = KEY_PRESSED_WAIT;
    key_item->key_timestamp = ms_tick;
    return;
  }
  
  if (key_item->state == KEY_PRESSED_WAIT)
  {
    uint32_t delta_time = ms_tick - key_item->key_timestamp;
    if (delta_time > KEY_PRESSED_TIME)
    {
      if (key_item->current_state != 0)
        key_item->state = KEY_PRESSED;
      else
        key_item->state = KEY_RELEASED;
    }
    return;
  }
  
  if ((key_item->state == KEY_PRESSED) || (key_item->state == KEY_HOLD))
  {
    // key not pressed
    if (key_item->current_state == 0)
    {
      key_item->state = KEY_WAIT_FOR_RELEASE;// key is locked here
      key_item->key_timestamp = ms_tick;
      return;
    }
  }
  
  if (key_item->state == KEY_WAIT_FOR_RELEASE)
  {
    uint32_t delta_time = ms_tick - key_item->key_timestamp;
    if (delta_time > KEY_RELEASE_TIME)
    {
      key_item->state = KEY_RELEASED;
      return;
    }
  }
  
  if ((key_item->state == KEY_PRESSED) && (key_item->current_state != 0))
  {
    //key still presed now
    uint32_t delta_time = ms_tick - key_item->key_timestamp;
    if (delta_time > KEY_HOLD_TIME)
    {
      key_item->state = KEY_HOLD;
      return;
    }
  }
}
