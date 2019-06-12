
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BNO080_SENSOR_H
#define __BNO080_SENSOR_H

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define MAX_PACKET_SIZE 128 //Packets can be up to 32k but we don't have that much RAM.
//Registers
#define CHANNEL_COMMAND         0
#define CHANNEL_EXECUTABLE      1
#define CHANNEL_CONTROL         2
#define CHANNEL_REPORTS         3
#define CHANNEL_WAKE_REPORTS    4
#define CHANNEL_GYRO            5

#define SHTP_REPORT_PRODUCT_ID_REQUEST  0xF9
#define SHTP_REPORT_PRODUCT_ID_RESPONSE 0xF8
#define SHTP_REPORT_SET_FEATURE_COMMAND 0xFD
#define SHTP_REPORT_BASE_TIMESTAMP 0xFB

#define SENSOR_REPORTID_ROTATION_VECTOR         0x05
#define SENSOR_REPORTID_GAME_ROTATION_VECTOR    0x08

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void bno080_init(void);
void bno080_init_gpio(void);
void bno080_init_wake_gpio(void);
void bno080_process(void);

#endif /* __BNO080_SENSOR_H */
