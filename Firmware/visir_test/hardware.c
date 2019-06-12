/* Includes ------------------------------------------------------------------*/
#include "hardware.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void hardware_init_rcc(void);
void hardware_opamp_init(void);

void hardware_dwt_init(void);
uint32_t hardware_dwt_get(void);
uint8_t hardware_dwt_comapre(int32_t tp);

uint8_t hardware_backlight_on = 0;
uint8_t hardware_backlight_value = 0;


/* Private functions ---------------------------------------------------------*/

void hardware_init_all(void)
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  
  hardware_init_rcc();
  
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq (&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);
  
  hardware_dwt_init();
  hardware_backlight_init();
  hardware_change_backlight(0, 30);//off
}

//Initialize main clock system
void hardware_init_rcc(void)
{
  //RCC_ClocksTypeDef RCC_ClockFreq;
  ErrorStatus HSEStartUpStatus;
  
  RCC_HSICmd(ENABLE);
  RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
  while(RCC_GetSYSCLKSource() != 0x00)
  {;}

  RCC_DeInit();
  RCC_HSEConfig(RCC_HSE_ON);
  // Wait till HSE is ready
  HSEStartUpStatus = RCC_WaitForHSEStartUp();
  if(HSEStartUpStatus == SUCCESS)
  {
    FLASH->ACR = FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_5WS;
    
    //FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
    //FLASH_SetLatency(FLASH_Latency_2);
    
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    RCC_PCLK2Config(RCC_HCLK_Div2);//APB2 < 90mhz
    RCC_PCLK1Config(RCC_HCLK_Div4);//<40mhz
    
    RCC_PLLConfig(RCC_PLLSource_HSE,4,168,2,7);
    //RCC_PLLConfig(RCC_PLLSource_HSE,8,336,2,7);
    RCC_PLLCmd(ENABLE);
    /* Wait till PLL is ready */
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {;}
    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08)
    {;}
  }
}

//Init DWT counter
void hardware_dwt_init(void)
{
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}


void hardware_backlight_init(void)
{
  RCC_APB2PeriphClockCmd(BACKLIGHT_TIMER_RCC, ENABLE);//Ftimer = SYSCLK
  RCC_AHB1PeriphClockCmd(BACKLIGHT_TIMER_GPIO_CLK, ENABLE);//PWM pin
  
  GPIO_InitTypeDef GPIO_InitStructure;
  
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = BACKLIGHT_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(BACKLIGHT_GPIO, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(BACKLIGHT_GPIO, BACKLIGHT_SRC, BACKLIGHT_AFIO);

  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;

  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);

  TIM_DeInit(BACKLIGHT_TIMER);

  TIM_TimeBaseStructure.TIM_Prescaler = BACKLIGHT_TIMER_PRESCALER - 1;
  TIM_TimeBaseStructure.TIM_Period = (BACKLIGHT_TIMER_PERIOD - 1);
  
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(BACKLIGHT_TIMER, &TIM_TimeBaseStructure);
  TIM_ARRPreloadConfig(BACKLIGHT_TIMER, ENABLE);
  
  TIM_OCStructInit(&TIM_OCInitStructure);
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = TIM_TimeBaseStructure.TIM_Period / 2;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC4Init(BACKLIGHT_TIMER, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(BACKLIGHT_TIMER, TIM_OCPreload_Enable);
  
  TIM_CtrlPWMOutputs(BACKLIGHT_TIMER, ENABLE);
  
  TIM_Cmd(BACKLIGHT_TIMER, ENABLE);
}

//state - 0-1
//value - 0-99
void hardware_change_backlight(uint8_t state, uint8_t value)
{
  if (state == 0)
  {
    TIM_SetCompare4(BACKLIGHT_TIMER, 0);
  }
  else
  {
    TIM_SetCompare4(BACKLIGHT_TIMER, value);
  }
  hardware_backlight_value = value;
  hardware_backlight_on = state;
}

void hardware_backlight_switch(void)
{
  hardware_change_backlight((hardware_backlight_on ^ 1), hardware_backlight_value);
}


// ***************************************************************************

uint32_t hardware_dwt_get(void)
{
  return DWT->CYCCNT;
}

inline uint8_t hardware_dwt_comapre(int32_t tp)
{
  return (((int32_t)hardware_dwt_get() - tp) < 0);
}

// Delay for "us"
void dwt_delay_us(uint32_t us)
{
  int32_t tp = hardware_dwt_get() + us * (SystemCoreClock / 1000000);
  while (hardware_dwt_comapre(tp));
}
