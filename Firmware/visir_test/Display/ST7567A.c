//----------------------------------------------------------------------
//EASTRISING TECHNOLOGY CO,.LTD.
// Encoding  : UTF8
// Module    : ERC12864-1 Series
// Create    : Alex_EXE ( http://alex-exe.ru ) + iliasam
// Source    : JAVEN
// Date      : 2014-08-17
// Drive IC  : ST7567A
// INTERFACE : SPI
// VDD		 : 3.3V
//----------------------------------------------------------------------
#include "ST7567A.h"

//unsigned char Contrast_level = 63; //0x15;
unsigned char Contrast_level = 5; //0x15;
unsigned char lcd_X = 0, lcd_Y = 0; //	Две глобальные переменные расположения курсора

// инициализация выводов МК для работы с дисплеем
void lcd_init_pins(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  
  GPIO_InitStructure.GPIO_Pin = DISPLAY_CLK_PIN | DISPLAY_MOSI_PIN;
  GPIO_Init(DISPLAY_CLK_GPIO, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = DISPLAY_DC_N_PIN;
  GPIO_Init(DISPLAY_DC_N_GPIO, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = DISPLAY_CS_N_PIN;
  GPIO_Init(DISPLAY_CS_N_GPIO, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = DISPLAY_PWR_N_PIN;
  GPIO_Init(DISPLAY_PWR_N_GPIO, &GPIO_InitStructure);
  
  display_enable_power();
}

void display_enable_power(void)
{
  GPIO_ResetBits(DISPLAY_PWR_N_GPIO, DISPLAY_PWR_N_PIN);
}

void display_disable_power(void)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  
  //GPIO_SetBits(DISPLAY_PWR_N_GPIO, DISPLAY_PWR_N_PIN);
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//deinit pins
  
  GPIO_InitStructure.GPIO_Pin = DISPLAY_CLK_PIN;
  GPIO_Init(DISPLAY_CLK_GPIO, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = DISPLAY_MOSI_PIN;
  GPIO_Init(DISPLAY_MOSI_GPIO, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = DISPLAY_DC_N_PIN;
  GPIO_Init(DISPLAY_DC_N_GPIO, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = DISPLAY_CS_N_PIN;
  GPIO_Init(DISPLAY_CS_N_GPIO, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = DISPLAY_RES_N_PIN;
  GPIO_Init(DISPLAY_RES_N_GPIO, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = DISPLAY_PWR_N_PIN;
  GPIO_Init(DISPLAY_PWR_N_GPIO, &GPIO_InitStructure);
}

// задержка
void lcd_delay(unsigned long p) 
{
  unsigned long i;
  for (i = 0; i < p; i++)
    ;
}

// отправить данные на дисплей
void lcd_write_data(unsigned char dat) 
{
  uint8_t i;
  //GPIO_ResetBits(lcd_port_control, lcd_pin_CS1);
  CS1_0
    //GPIO_SetBits(lcd_port_control, lcd_pin_RS);
    RS_1
      lcd_delay(2);
  for (i = 0; i < 8; i++) 
  {
    GPIO_ResetBits(DISPLAY_MOSI_GPIO, DISPLAY_CLK_PIN);
    lcd_delay(2);
    if (dat & 0x80)
      GPIO_SetBits(DISPLAY_MOSI_GPIO, DISPLAY_MOSI_PIN);
    else
      GPIO_ResetBits(DISPLAY_MOSI_GPIO, DISPLAY_MOSI_PIN);
    lcd_delay(2);
    GPIO_SetBits(DISPLAY_MOSI_GPIO, DISPLAY_CLK_PIN);
    lcd_delay(2);
    //dat = dat <<= 1;
    dat = dat << 1;
  }
  lcd_delay(2);
  //GPIO_SetBits(lcd_port_control, lcd_pin_CS1);
  CS1_1
    lcd_delay(2);
}

//	отправить команду на дисплей
void lcd_write_cmd(unsigned char cmd) 
{
  uint8_t i;
  //GPIO_ResetBits(lcd_port_control, lcd_pin_CS1);
  CS1_0
    //GPIO_ResetBits(lcd_port_control, lcd_pin_RS);
    RS_0
      lcd_delay(2);
  for (i = 0; i < 8; i++) 
  {
    GPIO_ResetBits(DISPLAY_MOSI_GPIO, DISPLAY_CLK_PIN);
    lcd_delay(2);
    if (cmd & 0x80)
      GPIO_SetBits(DISPLAY_MOSI_GPIO, DISPLAY_MOSI_PIN);
    else
      GPIO_ResetBits(DISPLAY_MOSI_GPIO, DISPLAY_MOSI_PIN);
    lcd_delay(2);
    GPIO_SetBits(DISPLAY_MOSI_GPIO, DISPLAY_CLK_PIN);
    lcd_delay(2);
    //cmd = cmd <<= 1;
    cmd = cmd << 1;
  }
  lcd_delay(2);
  //GPIO_SetBits(lcd_port_control, lcd_pin_CS1);
  CS1_1
    lcd_delay(2);
}

//	Адрес первой строки дисплея
//Specify DDRAM line for COM0 0~63
void lcd_Initial_Dispay_Line(unsigned char line) 
{
  line |= LCD_CMD_DISPLAY_START;
  lcd_write_cmd(line);
}

//	Установка строки (заменена lcd_gotoxy)
// Set page address 0~15
void lcd_Set_Page_Address(unsigned char add) 
{
  add = ST7567A_SET_PAGE | add;
  lcd_write_cmd(add);
}

//	Устрановка столбца (заменена lcd_gotoxy)
void lcd_Set_Column_Address(unsigned char add) 
{
  lcd_write_cmd((0x10 | (add >> 4)));
  lcd_write_cmd((0x0f & add));
}

//	Управление питанием
//Power_Control   4 (internal converte ON) + 2 (internal regulor ON) + 1 (internal follower ON)
void lcd_Power_Control(unsigned char vol) {
  //16
  lcd_write_cmd((0x28 | vol));
}

//
void lcd_Regulor_Resistor_Select(unsigned char r) {
  //  Regulor resistor select
  //            1+Rb/Ra  Vo=(1+Rb/Ra)Vev    Vev=(1-(63-a)/162)Vref   2.1v
  //            0  3.0       4  5.0(default)
  //            1  3.5       5  5.5
  //            2  4         6  6
  //            3  4.5       7  6.4
  lcd_write_cmd((0x20 | r));
}

//	Установка контрастности дисплея
//	Input : mod - контрастность от 0 до 63
void lcd_Set_Contrast_Control_Register(unsigned char mod) {
  //a(0-63) 32default   Vev=(1-(63-a)/162)Vref   2.1v
  lcd_write_cmd(0x81);
  lcd_write_cmd(mod);
}

//	инициализация дисплея
void lcd_init(void)
{
  lcd_write_cmd(0xe2); //RESET();
  lcd_delay(100);

  CS1_0
  lcd_write_cmd(0xe2);//RESET();
    
  lcd_delay(100000);
#if (INVERT_MODE==1)
  lcd_write_cmd(0xa1); //  Reverce disrect - horizontal
  lcd_write_cmd(0xc0); // Reverce SHL 1,COM0-COM63 - vertical
#else
  lcd_write_cmd(0xa0); //  Normal disrect (SEG0-SEG131) - ok (SEG Direction - horizontal)
  lcd_write_cmd(0xc8);// SHL 1,COM63-COM0 - ok - vertical
#endif
  
  //lcd_write_cmd(0xa1); //  Reverce disrect

  lcd_write_cmd(LCD_CMD_BIAS_9);
  
  lcd_Power_Control(0x07); //	voltage regulator internal Resistor ratio set	// write_cmd(0x2f);
  lcd_Regulor_Resistor_Select(5);//6 - maximum
  lcd_Set_Contrast_Control_Register(Contrast_level);
  
  uint8_t start_line = 0;
  lcd_Initial_Dispay_Line(start_line);
  lcd_write_cmd(LCD_CMD_DISPLAY_ON); //  Display on - ok
  
  lcd_delay(100000);
  
  lcd_write_cmd(0xa6); //  Инвертировать все точки - выкл - нормальный режим
  //lcd_write_cmd(0xa7);   //  Инвертировать все точки - вкл
  
  lcd_write_cmd(0xa4); //  Зажечь все точки - выкл - норальный режим
  //lcd_write_cmd(0xa5);   //  Зажечь все точки - вкл
  
  lcd_X = 0;
  lcd_Y = 0;
}

//	очистка дисплея
void lcd_clear(void)
{
  unsigned char i, j;
  
  for (i = 0; i < 8; i++) //clear page 0~7
  {
    lcd_write_cmd(ST7567A_SET_PAGE + i); //set page
    lcd_write_cmd(0X10); //set column
    lcd_write_cmd(0X00); //set column
    for (j = 0; j < 64; j++) //clear all columns upto 130
    {
      lcd_write_data(0x00);
    }
  }
}



//Send data from framebuffer to LCD
void lcd_send_full_framebuffer(uint8_t* data)
{
  unsigned char i, j;
  uint16_t data_counter = 0;
  
  for (i = 0; i < 8; i++) //page 0~7
  {
    lcd_write_cmd(ST7567A_SET_PAGE + i); //set page
    lcd_write_cmd(0x00); //set column
    lcd_write_cmd(0x10); //set column
    for (j = 0; j < 64; j++)
    {
      lcd_write_data(data[data_counter++]);
    }
  }
}