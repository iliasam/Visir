/* Includes ------------------------------------------------------------------*/
#include "power_controlling.h"
#include "hardware.h"
#include "stm32f4xx_gpio.h"
#include "ST7567A.h"
#include "mavlink_handling.h"
//#include "nvram.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define BATTERY_ADC_NAME        ADC1

#define BATTERY_ADC_CYCLES      256

#define BATTERY_ADC_MAX_VALUE   4095.0f

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile uint16_t raw_batt_value = 0;
volatile float battery_voltage = 0.0;

//extern nvram_data_t nvram_data;
extern volatile uint32_t ms_tick;

// Event time timestamp
uint32_t power_controlling_event_timestamp  = 0;

uint32_t power_controlling_time_from_event;

//Time of power off, ms
uint32_t power_controlling_power_off_time_ms = 300000;

/* Private function prototypes -----------------------------------------------*/
void power_controlling_init_adc(void);

/* Private functions ---------------------------------------------------------*/

void power_controlling_init(void)
{
  power_controlling_init_adc();
  power_controlling_update_power_off_time();
}

void power_controlling_update_power_off_time(void)
{
  //power_controlling_power_off_time_ms = nvram_data.power_off_time * 1000;
}

void power_controlling_init_adc(void)
{
  ADC_InitTypeDef ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  //RCC_ADCCLKConfig(RCC_ADC34PLLCLK_Div8);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  
  ADC_DeInit();
  
  // Calibration
  //ADC_VoltageRegulatorCmd(BATTERY_ADC_NAME, ENABLE);
  dwt_delay_us(1000);
  
  RCC_AHB1PeriphClockCmd(BATTERY_ADC_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin = BATTERY_ADC_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(BATTERY_ADC_GPIO, &GPIO_InitStructure);
  
    // ADC Common configuration *************************************************
  ADC_CommonStructInit(&ADC_CommonInitStructure);
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = 0;
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div6;
  ADC_CommonInit(&ADC_CommonInitStructure);
  
  ADC_StructInit(&ADC_InitStructure);
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 1;// One channel for this ADC
  ADC_Init(BATTERY_ADC_NAME, &ADC_InitStructure);
  
  ADC_RegularChannelConfig(
    BATTERY_ADC_NAME, BATTERY_ADC_PIN_CHANNEL, 1, ADC_SampleTime_480Cycles);
}

//Measure battery voltage
float power_controlling_meas_battery_voltage(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  //Set measurement GND to LOW
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = BATTERY_MEAS_GND_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(BATTERY_MEAS_GND_GPIO, &GPIO_InitStructure);
  GPIO_ResetBits(BATTERY_MEAS_GND_GPIO, BATTERY_MEAS_GND_PIN);
  
  
  ADC_Cmd(BATTERY_ADC_NAME, ENABLE);
  //while(!ADC_GetFlagStatus(BATTERY_ADC_NAME, ADC_FLAG_EOC));
  
  dwt_delay_us(1000);
  
  ADC_SoftwareStartConv(BATTERY_ADC_NAME);
      
  //skip first ADC cycles
  for (uint8_t i = 0; i < 16; i++)
  {
    while(ADC_GetFlagStatus(BATTERY_ADC_NAME, ADC_FLAG_EOC) == RESET);
  }
  
  uint32_t adc_summ = 0;
  
  for (uint16_t i = 0; i < BATTERY_ADC_CYCLES; i++)
  {
    while(ADC_GetFlagStatus(BATTERY_ADC_NAME, ADC_FLAG_EOC) == RESET);
    adc_summ += ADC_GetConversionValue(BATTERY_ADC_NAME);
  }

  //ADC_StopConversion(BATTERY_ADC_NAME);
  dwt_delay_us(500);
  ADC_Cmd(BATTERY_ADC_NAME, DISABLE);
  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_Init(BATTERY_MEAS_GND_GPIO, &GPIO_InitStructure);
  
  raw_batt_value = adc_summ / BATTERY_ADC_CYCLES;
  
  battery_voltage = (float)raw_batt_value * 
    MCU_VREF * BATTERY_DIV_VALUE / BATTERY_ADC_MAX_VALUE ;
  
  mavlink_send_battery_state(battery_voltage);
  
  return battery_voltage;
}

//Go to STANDBY mode
void power_controlling_enter_sleep(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
  dwt_delay_us(10);
  
  PWR_WakeUpPinCmd(ENABLE);
  SysTick->CTRL = 0;// disable Systick
  display_disable_power();
  __disable_irq();
    
  
  PWR_ClearFlag(PWR_FLAG_WU | PWR_FLAG_SB);//WU=WUF
  PWR_EnterSTANDBYMode();
}

// Some event was detected - reset "power_controlling_time_from_event" counter
void power_controlling_event(void)
{
  power_controlling_event_timestamp = ms_tick;
}

void power_controlling_handler(void)
{
  power_controlling_time_from_event = ms_tick - power_controlling_event_timestamp;
  
  //Do not sleep in debug mode
  if (power_controlling_is_debug() != 0)
    power_controlling_event();
  
  if (power_controlling_time_from_event > power_controlling_power_off_time_ms)
  {
    power_controlling_enter_sleep();
  }
}


uint8_t power_controlling_is_debug(void)
{
  if(CoreDebug->DHCSR & 1)
    return 1;
  else 
    return 0;
}


