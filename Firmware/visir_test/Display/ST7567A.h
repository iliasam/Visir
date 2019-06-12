#ifndef __ST7567A_H
#define __ST7567A_H

#include <stdint.h>
#include "config.h"
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

//#define INVERT_MODE				1						//	перевернуть дисплей


#define RS_0					GPIO_ResetBits(DISPLAY_DC_N_GPIO, DISPLAY_DC_N_PIN);
#define RS_1					GPIO_SetBits(DISPLAY_DC_N_GPIO, DISPLAY_DC_N_PIN);

#define CS1_0					GPIO_ResetBits(DISPLAY_CS_N_GPIO, DISPLAY_CS_N_PIN);
#define CS1_1					GPIO_SetBits(DISPLAY_CS_N_GPIO, DISPLAY_CS_N_PIN);

/** Command: set LCD bias to 1/9th */
#define LCD_CMD_BIAS_9				0xA2

/** Command: turn the display on */
#define LCD_CMD_DISPLAY_ON 		        0xaf //0b10101111

// Set start line - 0x40
#define LCD_CMD_DISPLAY_START		        0x40

/*
#define DISPLAY_ON()           Write_Instruction(0xaf)   //  Display on
#define DISPLAY_OFF()          Write_Instruction(0xae)   //  Display off
#define SET_ADC()              Write_Instruction(0xa1)   //  Reverse disrect (SEG131-SEG0)
#define CLEAR_ADC()            Write_Instruction(0xa0)   //  Normal disrect (SEG0-SEG131)
#define REVERSE_DISPLAY_ON()   Write_Instruction(0xa7)   //  Reverse display : 0 illuminated
#define REVERSE_DISPLAY_OFF()  Write_Instruction(0xa6)   //  Normal display : 1 illuminated
#define ENTIRE_DISPLAY_ON()    Write_Instruction(0xa5)   //  Entire dislay   Force whole LCD point
#define ENTIRE_DISPLAY_OFF()   Write_Instruction(0xa4)   //  Normal display
#define SET_BIAS()             Write_Instruction(0xa3)   //  bias 1
#define CLEAR_BIAS()           Write_Instruction(0xa2)   //  bias 0
#define SET_MODIFY_READ()      Write_Instruction(0xe0)   //  Stop automatic increment of the column address by the read instruction 
#define RESET_MODIFY_READ()    Write_Instruction(0xee)   //  Cancel Modify_read, column address return to its initial value just before the Set Modify Read instruction is started
#define RESET()                Write_Instruction(0xe2)
#define SET_SHL()              Write_Instruction(0xc8)   // SHL 1,COM63-COM0
#define CLEAR_SHL()            Write_Instruction(0xc0)   // SHL 0,COM0-COM63
*/

#define ST7567A_SET_PAGE        0xB0

//	инициализация выводов МК для работы с дисплеем
void lcd_init_pins(void);
//	задержка
void lcd_delay(unsigned long p);	//	задержка
#define DELAY_NOP				lcd_delay(10);

//	отправить данные на дисплей
void lcd_write_data(unsigned char dat);
//	отправить команду на дисплей
void lcd_write_cmd(unsigned char cmd);
//	Адрес первой строки дисплея
void lcd_Initial_Dispay_Line(unsigned char line);
//	Установка строки (заменена lcd_gotoxy)
void lcd_Set_Page_Address(unsigned char add);
//	Устрановка столбца (заменена lcd_gotoxy)
void lcd_Set_Column_Address(unsigned char add);
//	Управление питанием
void lcd_Power_Control(unsigned char vol);
//	Установка контрастности дисплея
//	Input : mod - контрастность от 0 до 63
void lcd_Set_Contrast_Control_Register(unsigned char mod);
void lcd_Regulor_Resistor_Select(unsigned char r);

void lcd_enable_power(void);
void lcd_disable_power(void);

//	инициализация дисплея
void lcd_init(void);

//	очистка дисплея
void lcd_clear(void);
//	Установка курсора
// 	Input : x,y - координаты символа
void lcd_gotoxy(unsigned char x,unsigned char y);
//	Преобразование символов через таблицу символов для вывода на дисплей
//	Input : с - символ в ASCII кодировке
unsigned char lcd_symbol_decode(unsigned char c);
//	Отправка символа на дисплей
//	Input : с - символ в ASCII кодировке
void lcd_putch(unsigned char c);
//	Отправка инвертированного символа на дисплей
//	Input : с - символ в ASCII кодировке
void lcd_putch_inv(unsigned char c);
//	Отправка строки на дисплей
//	Input : s - строка
void lcd_puts(char *s);
//	Отправка инвертированной строки на дисплей
//	Input : s - строка
void lcd_puts_inv(char *s);


void lcd_send_full_framebuffer(uint8_t* data);

void display_enable_power(void);
void display_disable_power(void);

#endif
