//SPP-C module
//the module default passcode is 1234.
//default baudrate - 9600

/* Includes ------------------------------------------------------------------*/
#include "config.h"
#include "main.h"
#include "bluetooth_comm.h"
#include "fifo_functions.h"
#include "stm32f4xx_rcc.h"
#include "mavlink_handling.h"
//#include "telescope_mode.h"


/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define BLUETOOTH_UART_DEFAULT_BAUDRATE                 115200

// Длина RX буфера FIFO, байт
#define BLUETOOTH_UART_RX_FIFO_SIZE                     256

// Длина TX буфера FIFO, байт
#define BLUETOOTH_UART_TX_FIFO_SIZE                     256

#define BLUETOOTH_UART_TX_DMA_SIZE                      256

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile uint8_t uart_rx_fifo_buf[BLUETOOTH_UART_RX_FIFO_SIZE];
volatile uint8_t uart_tx_fifo_buf[BLUETOOTH_UART_TX_FIFO_SIZE];

uint8_t uart_tx_dma_buf[BLUETOOTH_UART_TX_DMA_SIZE];

volatile fifo_struct_t uart_rx_fifo;
fifo_struct_t uart_tx_fifo;

uint8_t bluetooth_hw_detected = 0;

//this flag must be set in debugger
volatile uint8_t bluetooth_manual_cmd = 0;

uint8_t bluetooth_opened_flag = 0;

// enter Pole Star right ascention (AR: HH:MM:SS)
int poleAR_HH = 2;    // this means 2 hours, 52 minutes and 16 seconds
int poleAR_MM = 52;
int poleAR_SS = 16;

// enter Pole Star hour angle (H: HH:MM:SS)
int poleH_HH = 8;
int poleH_MM = 32;
int poleH_SS = 7;

/* Private function prototypes -----------------------------------------------*/
void bluetooth_init_gpio(void);
void bluetooth_init_uart(void);
void bluetooth_disable_uart(void);
void bluetooth_test_comm(void);
void bluetooth_send_manual_cmd(void);
void bluetooth_tx_process(void);
void bluetooth_init_uart_dma(void);
void bluetooth_dma_send_data(uint8_t* data, uint16_t size);

/* Private functions ---------------------------------------------------------*/

void bluetooth_init(void)
{
  bluetooth_init_gpio();
  bluetooth_init_uart();
  bluetooth_init_uart_dma();
  
  fifo_init_struct(
      (fifo_struct_t*)&uart_rx_fifo, 
      (uint8_t*)uart_rx_fifo_buf, 
      sizeof(uart_rx_fifo_buf));
  
    fifo_init_struct(
      (fifo_struct_t*)&uart_tx_fifo, 
      (uint8_t*)uart_tx_fifo_buf, 
      sizeof(uart_tx_fifo_buf));
  
  bluetooth_test_comm();
  bluetooth_send_manual_cmd();
}

void bluetooth_process(void)
{
  if ((BLUETOOTH_CONNECTED_GPIO->IDR & BLUETOOTH_CONNECTED_PIN) != 0)
    bluetooth_opened_flag = 1;
  else
    bluetooth_opened_flag = 0;
  
  uint8_t rx_byte;
  while (fifo_get_byte((fifo_struct_t*)&uart_rx_fifo, &rx_byte))
  {
    mavlink_parse_byte(rx_byte);
    //telescope_mode_parse_byte(rx_byte);
  }
  
  bluetooth_tx_process();
}

void bluetooth_tx_process(void)
{
  if (bluetooth_opened_flag == 0)
    return;
  
  if (BLUETOOTH_DMA_TX_STREAM->NDTR > 0) //dma is busy
    return;
  
  if (fifo_get_count((fifo_struct_t*)&uart_tx_fifo) < 5)
    return;
  
  uint16_t size_cnt = 0;
  uint8_t tx_byte;
  while (fifo_get_byte(&uart_tx_fifo, &tx_byte))
  {
    uart_tx_dma_buf[size_cnt] = tx_byte;
    size_cnt++;
  }
  bluetooth_dma_send_data(uart_tx_dma_buf, size_cnt);
  
  /*
  uint8_t tx_byte;
  while (fifo_get_byte((fifo_struct_t*)&uart_tx_fifo, &tx_byte))
  {
    while (USART_GetFlagStatus(BLUETOOTH_UART_NAME, USART_FLAG_TXE) == RESET);
    USART_SendData(BLUETOOTH_UART_NAME, (uint16_t)tx_byte);
  }
  */
}

void bluetooth_test_comm(void)
{
  uint8_t i = 0;
  Delay_ms(500);
  
  for (i=0; i<5; i++)
  {
    bluetooth_sw_send_data("AT\r\n", 4);
    Delay_ms(300);
    if (uart_rx_fifo.fifo_count > 3)
    {
      bluetooth_hw_detected = 1;
      return;
    }
  }
}

void bluetooth_send_manual_cmd(void)
{
  if (bluetooth_hw_detected == 0)
    return;
  
  if (bluetooth_manual_cmd == 0)
    return;
  
  Delay_ms(300);
  //bluetooth_sw_send_data("AT+BAUD4\r\n", 10);//4 - 9600
  bluetooth_sw_send_data("AT+BAUD8\r\n", 10);//8 - 115200
}

void bluetooth_init_gpio(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_AHB1PeriphClockCmd(BLUETOOTH_UART_GPIO_CLK, ENABLE);
  
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  
  GPIO_InitStructure.GPIO_Pin = BLUETOOTH_UART_RX_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(BLUETOOTH_UART_RX_GPIO, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = BLUETOOTH_UART_TX_PIN;
  GPIO_Init(BLUETOOTH_UART_TX_GPIO, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(
    BLUETOOTH_UART_RX_GPIO, BLUETOOTH_UART_RX_PIN_SRC, BLUETOOTH_UART_AF_NAME);
  GPIO_PinAFConfig(
    BLUETOOTH_UART_TX_GPIO, BLUETOOTH_UART_TX_PIN_SRC, BLUETOOTH_UART_AF_NAME);
  
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Pin = BLUETOOTH_CONNECTED_PIN;
  GPIO_Init(BLUETOOTH_CONNECTED_GPIO, &GPIO_InitStructure);
}

void bluetooth_init_uart(void)
{
  USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  RCC_APB2PeriphClockCmd(BLUETOOTH_UART_CLK, ENABLE);
  
  USART_StructInit(&USART_InitStructure);
  USART_InitStructure.USART_BaudRate = BLUETOOTH_UART_DEFAULT_BAUDRATE;
  USART_Init(BLUETOOTH_UART_NAME, &USART_InitStructure);
  
  USART_ITConfig(BLUETOOTH_UART_NAME, USART_IT_RXNE, ENABLE);
  
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  USART_DMACmd(BLUETOOTH_UART_NAME, USART_DMAReq_Tx, ENABLE);
  
  USART_Cmd(BLUETOOTH_UART_NAME, ENABLE);
}

void bluetooth_init_uart_dma(void)
{
  DMA_InitTypeDef DMA_InitStructure;
  RCC_AHB1PeriphClockCmd(BLUETOOTH_DMA_RCC, ENABLE);
  
  DMA_DeInit(BLUETOOTH_DMA_TX_STREAM);
  DMA_StructInit(&DMA_InitStructure);
  DMA_InitStructure.DMA_Channel = BLUETOOTH_DMA_TX_CH;
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&BLUETOOTH_UART_NAME->DR;
  DMA_InitStructure.DMA_Memory0BaseAddr = 0;//not used now
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
  DMA_InitStructure.DMA_BufferSize = 0;//not used now
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
  DMA_Init(BLUETOOTH_DMA_TX_STREAM, &DMA_InitStructure);
}

void bluetooth_disable_uart(void)
{
  USART_ITConfig(BLUETOOTH_UART_NAME, USART_IT_RXNE, DISABLE);
  USART_Cmd(BLUETOOTH_UART_NAME, DISABLE);
}


//Polling sending data to the bluetooth
void bluetooth_sw_send_data(uint8_t* data, uint16_t size)
{
  uint8_t i;

  while (USART_GetFlagStatus(BLUETOOTH_UART_NAME, USART_FLAG_TXE) == RESET);
  
  for (i=0; i < size; i++)
  {
    while (USART_GetFlagStatus(BLUETOOTH_UART_NAME, USART_FLAG_TXE) == RESET);
    USART_SendData(BLUETOOTH_UART_NAME, (uint16_t)data[i]);
  }
}

// Отправить данные через DMA
void bluetooth_dma_send_data(uint8_t* data, uint16_t size)
{
  if (BLUETOOTH_DMA_TX_STREAM->NDTR > 0)
    return;
  
  DMA_Cmd(BLUETOOTH_DMA_TX_STREAM, DISABLE);
  
  DMA_ClearITPendingBit(BLUETOOTH_DMA_TX_STREAM, DMA_IT_TCIF7);//без этого не работает?
  BLUETOOTH_DMA_TX_STREAM->NDTR = size;
  BLUETOOTH_DMA_TX_STREAM->M0AR = (uint32_t)data;
  DMA_Cmd(BLUETOOTH_DMA_TX_STREAM, ENABLE);
}

void bluetooth_add_data_for_tx(uint8_t* data, uint16_t size)
{
  if (bluetooth_opened_flag == 0)
    return;
  
  fifo_add_data((fifo_struct_t*)&uart_tx_fifo, data, size);
  //bluetooth_sw_send_data(data, size);
}

void BLUETOOTH_UART_IRQ_HANDLER(void)
{
  /* USART in Receiver mode */
  if (USART_GetITStatus(BLUETOOTH_UART_NAME, USART_IT_RXNE) == SET)
  {
    uint16_t tmp_rx_data = USART_ReceiveData(BLUETOOTH_UART_NAME);
    fifo_add_byte((fifo_struct_t*)&uart_rx_fifo, (uint8_t)tmp_rx_data);
    
    //USART_ITConfig(BLUETOOTH_UART_NAME, USART_IT_RXNE, DISABLE);
  }
  else
  {
    asm("nop");
  }
}
