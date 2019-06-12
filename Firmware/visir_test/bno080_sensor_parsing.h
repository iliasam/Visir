
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BNO080_SENSOR_PARSING_H
#define __BNO080_SENSOR_PARSING_H

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  float i; //x
  float j; //y
  float k; //z
  float real; //w
  float accur;
  uint8_t state;
  float yaw_correction;//коррекци в градуса - это кривое решение
} quaternion_t;

typedef struct
{
  float roll;
  float pitch;
  float yaw;
  float raw_yaw;
  float accur;
  uint8_t state;  
} euler_angles_t;


/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void bno080_parse_input_report(void);
void bno080_set_yaw_correction(uint8_t vector_type, float value);
void bno080_set_yaw_correction_by_real_angle(float real_angle);

#endif /* __BNO080_SENSOR_PARSING_H */
