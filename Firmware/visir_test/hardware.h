/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HARDWARE_H
#define __HARDWARE_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "config.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void hardware_init_all(void);
void dwt_delay_us(uint32_t us);
void hardware_backlight_init(void);
void hardware_change_backlight(uint8_t state, uint8_t value);
void hardware_backlight_switch(void);

#endif /* __HARDWARE_H */
