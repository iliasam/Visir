
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BLUETOOTH_COMM_H
#define __BLUETOOTH_COMM_H

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void bluetooth_init(void);
void bluetooth_sw_send_data(uint8_t* data, uint16_t size);
void bluetooth_add_data_for_tx(uint8_t* data, uint16_t size);
void bluetooth_process(void);

#endif /* __BLUETOOTH_COMM_H */
