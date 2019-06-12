// particly aken from here: 
// https://github.com/sparkfun/SparkFun_BNO080_Arduino_Library/

/* Includes ------------------------------------------------------------------*/
#include "config.h"
#include "main.h"
#include "bno080_sensor.h"
#include "bno080_sensor_parsing.h"
#include "fifo_functions.h"
#include "stm32f4xx_rcc.h"


/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/



/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t shtpHeader[4]; //Each packet has a header of 4 bytes
uint8_t shtpData[MAX_PACKET_SIZE];
uint8_t sequenceNumber[6] = {0, 0, 0, 0, 0, 0}; //There are 6 com channels. Each channel has its own seqnum
uint8_t commandSequenceNumber = 0; //Commands have a seqNum as well. These are inside command packet

uint8_t bno080_is_initialized = 0;

/* Private function prototypes -----------------------------------------------*/

void bno080_init_spi(void);
void bno080_select_chip(void);
void bno080_deselect_chip(void);
uint8_t bno080_receive_packet(void);
uint8_t bno080_transfer_byte(uint8_t byte);
uint8_t bno080_comm_start(void);
uint8_t bno080_send_packet(uint8_t channelNumber, uint8_t dataLength);
void bno080_wait_for_int(void);
void bno080_activate_wake(void);
void bno080_deactivate_wake(void);
void bno080_set_feature_command(
  uint8_t reportID, uint16_t timeBetweenReports, uint32_t specificConfig);
uint8_t bno080_check_new_data(void);

/* Private functions ---------------------------------------------------------*/

void bno080_init(void)
{
  bno080_init_gpio();
  bno080_init_spi();
  if (bno080_comm_start())
  {
    bno080_set_feature_command(SENSOR_REPORTID_ROTATION_VECTOR, 100, 0);
    bno080_set_feature_command(SENSOR_REPORTID_GAME_ROTATION_VECTOR, 100, 0);
    bno080_is_initialized = 1;
  }
}

//Нужно вызвать. чтобы PS0/WAKE оказался в 1, и включился режим SPI
void bno080_init_wake_gpio(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Pin = BNO080_WAKE_PIN;
  GPIO_Init(BNO080_WAKE_GPIO, &GPIO_InitStructure);
  bno080_deactivate_wake();
}


void bno080_init_gpio(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(BNO080_GPIO_CLK, ENABLE);
  
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  
  GPIO_InitStructure.GPIO_Pin = BNO080_CLK_PIN;
  GPIO_Init(BNO080_CLK_GPIO, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = BNO080_MOSI_PIN;
  GPIO_Init(BNO080_MOSI_GPIO, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = BNO080_MISO_PIN;
  GPIO_Init(BNO080_MISO_GPIO, &GPIO_InitStructure);
  
  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Pin = BNO080_CS_N_PIN;
  GPIO_Init(BNO080_CS_N_GPIO, &GPIO_InitStructure);
  bno080_deselect_chip();
  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Pin = BNO080_INT_PIN;
  GPIO_Init(BNO080_INT_GPIO, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(BNO080_CLK_GPIO,BNO080_CLK_SRC, BNO080_CLK_AFIO);
  GPIO_PinAFConfig(BNO080_MOSI_GPIO, BNO080_MOSI_SRC, BNO080_MOSI_AFIO);
  GPIO_PinAFConfig(BNO080_MISO_GPIO, BNO080_MISO_SRC, BNO080_MISO_AFIO);
}

void bno080_process(void)
{
  if (bno080_is_initialized == 0)
    return;
  
  bno080_check_new_data();
    
}

uint8_t bno080_check_new_data(void)
{
  if ((BNO080_INT_GPIO->IDR & BNO080_INT_PIN) != 0)
    return 0; //no HINT
  
  if (bno080_receive_packet() == 1)
  {
    if (shtpHeader[2] == CHANNEL_REPORTS && 
        shtpData[0] == SHTP_REPORT_BASE_TIMESTAMP)
    {
      //This will update the rawAccelX, etc variables depending on which feature report is found
      bno080_parse_input_report(); 
      return 1;
    }
  }
  return 0;
}



//start communication
uint8_t bno080_comm_start(void)
{
  //At system startup, the hub must send its full advertisement message (see 5.2 and 5.3) to the
  //host. It must not send any other data until this step is complete.
  bno080_wait_for_int();
  bno080_receive_packet();

  //тут принимается короткий пакет - 5 байт
  bno080_wait_for_int();
  bno080_receive_packet();
  
  Delay_ms(1);
 
  bno080_wait_for_int();//unsolicited Initialize Response ??
  bno080_receive_packet();
  
  //Check communication with device
  shtpData[0] = SHTP_REPORT_PRODUCT_ID_REQUEST; //Request the product ID and reset info
  shtpData[1] = 0; //Reserved
  bno080_send_packet(CHANNEL_CONTROL, 2);

  //Now we wait for response
  bno080_wait_for_int();
  if (bno080_receive_packet() == 1)
  {
    if (shtpData[0] == SHTP_REPORT_PRODUCT_ID_RESPONSE)
      return 1;
  }
  
  return 0; //Something went wrong
}

void bno080_set_feature_command(
  uint8_t reportID, uint16_t timeBetweenReports, uint32_t specificConfig)
{
  long microsBetweenReports = (long)timeBetweenReports * 1000L;
  
  shtpData[0] = SHTP_REPORT_SET_FEATURE_COMMAND; //Set feature command. Reference page 55
  shtpData[1] = reportID; //Feature Report ID. 0x01 = Accelerometer, 0x05 = Rotation vector
  shtpData[2] = 0; //Feature flags
  shtpData[3] = 0; //Change sensitivity (LSB)
  shtpData[4] = 0; //Change sensitivity (MSB)
  shtpData[5] = (microsBetweenReports >> 0) & 0xFF;  //Report interval (LSB) in microseconds. 0x7A120 = 500ms
  shtpData[6] = (microsBetweenReports >> 8) & 0xFF;  //Report interval
  shtpData[7] = (microsBetweenReports >> 16) & 0xFF; //Report interval
  shtpData[8] = (microsBetweenReports >> 24) & 0xFF; //Report interval (MSB)
  shtpData[9] = 0; //Batch Interval (LSB)
  shtpData[10] = 0; //Batch Interval
  shtpData[11] = 0; //Batch Interval
  shtpData[12] = 0; //Batch Interval (MSB)
  shtpData[13] = (specificConfig >> 0) & 0xFF;	   //Sensor-specific config (LSB)
  shtpData[14] = (specificConfig >> 8) & 0xFF;	   //Sensor-specific config
  shtpData[15] = (specificConfig >> 16) & 0xFF;	  //Sensor-specific config
  shtpData[16] = (specificConfig >> 24) & 0xFF;	  //Sensor-specific config (MSB)
  
  //Transmit packet on channel 2, 17 bytes
  bno080_send_packet(CHANNEL_CONTROL, 17);
}

uint8_t bno080_receive_packet(void)
{
  bno080_select_chip();
  
  //Get the first four bytes, aka the packet header
  uint8_t packetLSB = bno080_transfer_byte(0);
  uint8_t packetMSB = bno080_transfer_byte(0);
  uint8_t channelNumber = bno080_transfer_byte(0);
  uint8_t sequenceNumber = bno080_transfer_byte(0); //Not sure if we need to store this or not
  
  //Store the header info
  shtpHeader[0] = packetLSB;
  shtpHeader[1] = packetMSB;
  shtpHeader[2] = channelNumber;
  shtpHeader[3] = sequenceNumber;
  
  //Calculate the number of data bytes in this packet
  int16_t dataLength = ((uint16_t)packetMSB << 8 | (uint16_t)packetLSB);
  dataLength &= ~(1 << 15); //Clear the MSbit.
  //This bit indicates if this package is a continuation of the last. Ignore it for now.
  //TODO catch this as an error and exit
  
  if (dataLength == 0)
  {
    //Packet is empty
    bno080_deselect_chip();//???
    return 0; //All done
  }
  
  if ((packetMSB == 0xFF) && (packetLSB == 0xFF))
    return 0;

  dataLength -= 4; //Remove the header bytes from the data count
  
  //Read incoming data into the shtpData array
  for (uint16_t dataSpot = 0; dataSpot < dataLength; dataSpot++)
  {
    uint8_t incoming = bno080_transfer_byte(0);
    if (dataSpot < MAX_PACKET_SIZE)  //BNO080 can respond with upto 270 bytes, avoid overflow
      shtpData[dataSpot] = incoming; //Store data into the shtpData array
  }
  
  bno080_deselect_chip();
  
  return 1; //All done
}

uint8_t bno080_send_packet(uint8_t channelNumber, uint8_t dataLength)
{
  uint8_t packetLength = dataLength + 4; //Add four bytes for the header
  
  bno080_activate_wake();
  bno080_wait_for_int();
  
  bno080_select_chip();
  bno080_deactivate_wake();
  
  //Send the 4 byte packet header
  bno080_transfer_byte(packetLength & 0xFF);    //Packet length LSB
  bno080_transfer_byte(packetLength >> 8);      //Packet length MSB
  bno080_transfer_byte(channelNumber);          //Channel number
  bno080_transfer_byte(sequenceNumber[channelNumber]++); //Send the sequence number, increments with each packet sent, different 
  
  //Send the user's data packet
  for (uint8_t i = 0; i < dataLength; i++)
  {
    bno080_transfer_byte(shtpData[i]);
  }
  
  bno080_deselect_chip();
  return 1;
}

void bno080_init_spi(void)
{
  SPI_InitTypeDef  SPI_InitStructure;
  
  RCC_APB2PeriphClockCmd(BNO080_SPI_CLK, ENABLE);
  
  SPI_I2S_DeInit(BNO080_SPI_NAME);
  SPI_StructInit(&SPI_InitStructure);
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  //SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_Init(BNO080_SPI_NAME, &SPI_InitStructure);
  
  SPI_Cmd(BNO080_SPI_NAME, ENABLE);
}

uint8_t bno080_transfer_byte(uint8_t byte)
{
  while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE));  //transmit buffer empty?
  SPI_I2S_SendData(BNO080_SPI_NAME, byte);
  while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE)); //data received?
  return (uint8_t)SPI_I2S_ReceiveData(BNO080_SPI_NAME);
}

void bno080_select_chip(void)
{
  BNO080_CS_N_GPIO->ODR &= ~BNO080_CS_N_PIN;
}

void bno080_deselect_chip(void)
{
  BNO080_CS_N_GPIO->ODR |= BNO080_CS_N_PIN;
}

void bno080_activate_wake(void)
{
  BNO080_WAKE_GPIO->ODR &= ~BNO080_WAKE_PIN;
}

void bno080_deactivate_wake(void)
{
  BNO080_WAKE_GPIO->ODR |= BNO080_WAKE_PIN;
}

void bno080_wait_for_int(void)
{
  //int is active low
  while ((BNO080_INT_GPIO->IDR & BNO080_INT_PIN) != 0)
  {
    asm("nop");
  }
}

