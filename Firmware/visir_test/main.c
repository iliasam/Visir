//STM32F405RGt6

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_rcc.h"
#include "ST7567A.h"
#include "lcd_worker.h"
#include "bluetooth_comm.h"
#include "bno080_sensor.h"
#include "hardware.h"
#include "power_controlling.h"
#include "bno080_sensor_parsing.h"
#include "keys_controlling.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
// Variable to count 1 ms periods
uint32_t timer_1ms = 0;

// Variable to count 10 ms periods
uint32_t timer_10ms = 0;

// Variable to count 10 ms periods
uint32_t timer_100ms = 0;

// Variable to count 100 ms periods
uint32_t timer_1000ms = 0;

extern euler_angles_t euler_rotation_vector;
extern euler_angles_t euler_game_rotation_vector;//gyro

//extern uint8_t telescope_mode_enabled;
extern uint8_t hardware_backlight_on;

char tmp_str[32];

/* Private function prototypes -----------------------------------------------*/
void Delay_ms(uint32_t ms);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  hardware_init_all();
  
  display_disable_power();
  bno080_init_wake_gpio();
  bno080_init_gpio();
  
  Delay_ms(100);
  
  lcd_init_pins();
  Delay_ms(200);
  lcd_init();
  Delay_ms(100);
  bluetooth_init();
  bno080_init();
  power_controlling_init();
  keys_init();
  
  lcd_full_clear();
  lcd_draw_string(" >< ", 27, 17, FONT_SIZE_11, 0);
  //lcd_draw_string("TEST1", 25, 22, FONT_SIZE_11, 0);
  //lcd_draw_string("100 M", 34, 30, FONT_SIZE_6, 0);
  //draw_black_line(27);
    
  lcd_update();
  
  while(1)
  {
    if (TIMER_ELAPSED(timer_1ms))
    {
      START_TIMER(timer_1ms, 1);
      bluetooth_process();
      bno080_process();
      //key_handling();
    }
    
    if (TIMER_ELAPSED(timer_10ms))
    {
      START_TIMER(timer_10ms, 10);
      
      power_controlling_handler();
      key_handling();
    }
    
    if (TIMER_ELAPSED(timer_100ms))
    {
      START_TIMER(timer_100ms, 100);
      
      sprintf(tmp_str, "%.1f   ", euler_game_rotation_vector.yaw);
      lcd_draw_string(tmp_str, 34, 7, FONT_SIZE_6, 0);

      sprintf(tmp_str, "%.1f   ", euler_rotation_vector.yaw);
      lcd_draw_string(tmp_str, 34, 35, FONT_SIZE_6, 0);

      
      //DISPLAY BACKLIGHT
      if (hardware_backlight_on)
      {
        lcd_draw_string("B", 25, 20, FONT_SIZE_6, 0);
      }
      else
      {
        lcd_draw_string(" ", 25, 20, FONT_SIZE_6, 0);
      }
      
      lcd_update();
    }
    
    if (TIMER_ELAPSED(timer_1000ms))
    {
      START_TIMER(timer_1000ms, 1000);
      power_controlling_meas_battery_voltage();
    }
  }
}

void Delay_ms(uint32_t ms)
{
  volatile uint32_t nCount;
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq (&RCC_Clocks);
  nCount=(RCC_Clocks.HCLK_Frequency/10000)*ms;
  for (; nCount!=0; nCount--);
}

