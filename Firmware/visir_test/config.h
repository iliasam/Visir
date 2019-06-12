/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CONFIG_H
#define __CONFIG_H

/* Includes ------------------------------------------------------------------*/

// BUTTONS ********************************************************************
// Button 1 - wakeup
#define BUTTON_1_GPIO           GPIOA
#define BUTTON_1_PIN            GPIO_Pin_0

// Button 2
#define BUTTON_2_GPIO           GPIOA
#define BUTTON_2_PIN            GPIO_Pin_1

// DISPLAY ********************************************************************

#define DISPLAY_SPI_NAME        SPI2

// Display power - active low
#define DISPLAY_PWR_N_GPIO      GPIOB
#define DISPLAY_PWR_N_PIN       GPIO_Pin_9

// Data/command line - high(data) / low(command)
#define DISPLAY_DC_N_GPIO       GPIOC
#define DISPLAY_DC_N_PIN        GPIO_Pin_6

// Display reset - active low - NOT USED
#define DISPLAY_RES_N_GPIO      GPIOB
#define DISPLAY_RES_N_PIN       GPIO_Pin_0

// SPI CSn
#define DISPLAY_CS_N_GPIO       GPIOC
#define DISPLAY_CS_N_PIN        GPIO_Pin_8

// SPI CLK
#define DISPLAY_CLK_GPIO        GPIOB
#define DISPLAY_CLK_PIN         GPIO_Pin_13
#define DISPLAY_CLK_SRC         GPIO_PinSource13
#define DISPLAY_CLK_AFIO        GPIO_AF_5

// SPI MOSI
#define DISPLAY_MOSI_GPIO       GPIOB
#define DISPLAY_MOSI_PIN        GPIO_Pin_15
#define DISPLAY_MOSI_SRC        GPIO_PinSource15
#define DISPLAY_MOSI_AFIO       GPIO_AF_5


// ADC ************************************************************************

#define ADC_SAMPLING_TIME       ADC_SampleTime_1Cycles5

#define MCU_VREF                3.3f 


// POWER CONTROLLING **********************************************************
#define BATTERY_ADC_GPIO_CLK            RCC_AHB1Periph_GPIOC
#define BATTERY_ADC_GPIO                GPIOC
#define BATTERY_ADC_PIN                 GPIO_Pin_0 //BAT_VOLT
#define BATTERY_ADC_PIN_CHANNEL         ADC_Channel_10 //ADC4

// Battery divider GND
#define BATTERY_MEAS_GND_GPIO           GPIOC
#define BATTERY_MEAS_GND_PIN            GPIO_Pin_1 //MEAS_GND

// Battery voltage divider coefficient
#define BATTERY_DIV_VALUE               (2.0f)

// BLUETOOTH **********************************************************

#define BLUETOOTH_UART_NAME             USART1
#define BLUETOOTH_UART_AF_NAME          GPIO_AF_USART2

#define BLUETOOTH_UART_GPIO_CLK         RCC_AHB1Periph_GPIOA

#define BLUETOOTH_UART_CLK              RCC_APB2Periph_USART1

#define BLUETOOTH_UART_RX_PIN           GPIO_Pin_10
#define BLUETOOTH_UART_RX_PIN_SRC       GPIO_PinSource10
#define BLUETOOTH_UART_RX_GPIO          GPIOA

#define BLUETOOTH_UART_TX_PIN           GPIO_Pin_9
#define BLUETOOTH_UART_TX_PIN_SRC       GPIO_PinSource9
#define BLUETOOTH_UART_TX_GPIO          GPIOA

#define BLUETOOTH_UART_IRQ_HANDLER      USART1_IRQHandler

//Pin goes high when the port is opened
#define BLUETOOTH_CONNECTED_PIN         GPIO_Pin_5
#define BLUETOOTH_CONNECTED_GPIO        GPIOB

#define BLUETOOTH_DMA_RCC               RCC_AHB1Periph_DMA2
#define BLUETOOTH_DMA_TX_STREAM         DMA2_Stream7
#define BLUETOOTH_DMA_TX_CH             DMA_Channel_4

// BNO080 MEMS **********************************************************
#define BNO080_SPI_NAME         SPI1
#define BNO080_GPIO_CLK         RCC_AHB1Periph_GPIOA
#define BNO080_SPI_CLK          RCC_APB2Periph_SPI1

// SPI CSn
#define BNO080_CS_N_GPIO        GPIOA
#define BNO080_CS_N_PIN         GPIO_Pin_2

// SPI CLK
#define BNO080_CLK_GPIO         GPIOA
#define BNO080_CLK_PIN          GPIO_Pin_5
#define BNO080_CLK_SRC          GPIO_PinSource5
#define BNO080_CLK_AFIO         GPIO_AF_SPI1

// SPI MOSI
#define BNO080_MOSI_GPIO        GPIOA
#define BNO080_MOSI_PIN         GPIO_Pin_7
#define BNO080_MOSI_SRC         GPIO_PinSource7
#define BNO080_MOSI_AFIO        GPIO_AF_SPI1

// SPI MISO
#define BNO080_MISO_GPIO        GPIOA
#define BNO080_MISO_PIN         GPIO_Pin_6
#define BNO080_MISO_SRC         GPIO_PinSource6
#define BNO080_MISO_AFIO        GPIO_AF_SPI1

#define BNO080_INT_GPIO         GPIOA
#define BNO080_INT_PIN          GPIO_Pin_3

#define BNO080_WAKE_GPIO        GPIOC
#define BNO080_WAKE_PIN         GPIO_Pin_9

//BACKLIGHT ****************************************************

#define BACKLIGHT_TIMER_RCC             RCC_APB2Periph_TIM1
#define BACKLIGHT_TIMER_GPIO_CLK        RCC_AHB1Periph_GPIOA
#define BACKLIGHT_TIMER                 TIM1
#define BACKLIGHT_TIMER_FREQUENCY       10000 //hz
#define BACKLIGHT_TIMER_PRESCALER       (SystemCoreClock / BACKLIGHT_TIMER_PERIOD / BACKLIGHT_TIMER_FREQUENCY)
#define BACKLIGHT_TIMER_PERIOD          (100)

#define BACKLIGHT_GPIO                  GPIOA
#define BACKLIGHT_PIN                   GPIO_Pin_11
#define BACKLIGHT_SRC                   GPIO_PinSource11
#define BACKLIGHT_AFIO                  GPIO_AF_TIM1

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __CONFIG_H */
