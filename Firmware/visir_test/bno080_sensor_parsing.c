// particly aken from here: 
// https://github.com/sparkfun/SparkFun_BNO080_Arduino_Library/

/* Includes ------------------------------------------------------------------*/
#include "config.h"
#include "main.h"
#include "bno080_sensor.h"
#include "bno080_sensor_parsing.h"
#include "mavlink_handling.h"
#include <math.h>

/* Private typedef -----------------------------------------------------------*/
#define ROTATION_VECTOR_Q1      ((int16_t)14)

#define RADIANS_TO_DEGREES_MULTIPLIER   57.29578f

//sqrt(2)/2
#define SQR2 0.7071067812f;


/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern uint8_t shtpHeader[4]; //Each packet has a header of 4 bytes
extern uint8_t shtpData[MAX_PACKET_SIZE];

extern uint8_t telescope_mode_enabled;//todo

uint32_t timeStamp;
uint16_t rawQuatI, rawQuatJ, rawQuatK, rawQuatReal, rawQuatRadianAccuracy, quatAccuracy;

quaternion_t rotation_vector;
quaternion_t game_rotation_vector;//gyro

euler_angles_t euler_rotation_vector;
euler_angles_t euler_game_rotation_vector;//gyro

/* Private function prototypes -----------------------------------------------*/
float bno080_qToFloat(int16_t fixedPointValue, uint8_t qPoint);
euler_angles_t bno080_quat_to_euler(quaternion_t* quat);
quaternion_t bno080_rotate_quaternion(quaternion_t* quat);

//Истинный азимут на калибровочный объект 
float bno080_real_correction_angle = 0.0f;

/* Private functions ---------------------------------------------------------*/
void bno080_parse_input_report(void)
{
  //Calculate the number of data bytes in this packet
  int16_t dataLength = ((uint16_t)shtpHeader[1] << 8 | shtpHeader[0]);
  dataLength &= ~(1 << 15); //Clear the MSbit. This bit indicates if this package is a continuation of the last.
  //Ignore it for now. TODO catch this as an error and exit
  
  dataLength -= 4; //Remove the header bytes from the data count
  
  timeStamp = ((uint32_t)shtpData[4] << (8 * 3)) | (shtpData[3] << (8 * 2)) | (shtpData[2] << (8 * 1)) | (shtpData[1] << (8 * 0));
  
  uint8_t status = shtpData[5 + 2] & 0x03; //Get status bits
  uint16_t data1 = (uint16_t)shtpData[5 + 5] << 8 | shtpData[5 + 4];
  uint16_t data2 = (uint16_t)shtpData[5 + 7] << 8 | shtpData[5 + 6];
  uint16_t data3 = (uint16_t)shtpData[5 + 9] << 8 | shtpData[5 + 8];
  uint16_t data4 = 0;
  uint16_t data5 = 0;
  
  if (dataLength - 5 > 9)
  {
    data4 = (uint16_t)shtpData[5 + 11] << 8 | shtpData[5 + 10];
  }
  if (dataLength - 5 > 11)
  {
    data5 = (uint16_t)shtpData[5 + 13] << 8 | shtpData[5 + 12];
  }
  
  if (shtpData[5] == SENSOR_REPORTID_ROTATION_VECTOR)
  {
    quatAccuracy = status;
    rawQuatI = data1;
    rawQuatJ = data2;
    rawQuatK = data3;
    rawQuatReal = data4;
    rawQuatRadianAccuracy = data5; //Only available on rotation vector, not game rot vector
    
    quaternion_t rotation_vector_raw;
    rotation_vector_raw.real = bno080_qToFloat(rawQuatReal, ROTATION_VECTOR_Q1);
    rotation_vector_raw.i = bno080_qToFloat(rawQuatI, ROTATION_VECTOR_Q1);
    rotation_vector_raw.j = bno080_qToFloat(rawQuatJ, ROTATION_VECTOR_Q1);
    rotation_vector_raw.k = bno080_qToFloat(rawQuatK, ROTATION_VECTOR_Q1);
    rotation_vector_raw.yaw_correction = rotation_vector.yaw_correction;//криво
    
    rotation_vector = bno080_rotate_quaternion(&rotation_vector_raw);
    rotation_vector.accur = bno080_qToFloat(
      rawQuatRadianAccuracy, ROTATION_VECTOR_Q1);
    rotation_vector.state = quatAccuracy;
    
    euler_rotation_vector = bno080_quat_to_euler(&rotation_vector);
    mavlink_send_rotation_vector(&euler_rotation_vector);
    mavlink_send_quaternion(&rotation_vector);
  }
  else if (shtpData[5] == SENSOR_REPORTID_GAME_ROTATION_VECTOR)
  {
    quatAccuracy = status;
    rawQuatI = data1;
    rawQuatJ = data2;
    rawQuatK = data3;
    rawQuatReal = data4;
    rawQuatRadianAccuracy = data5; //Only available on rotation vector, not game rot vector
    
    quaternion_t rotation_vector_raw;
    rotation_vector_raw.real = bno080_qToFloat(rawQuatReal, ROTATION_VECTOR_Q1);
    rotation_vector_raw.i = bno080_qToFloat(rawQuatI, ROTATION_VECTOR_Q1);
    rotation_vector_raw.j = bno080_qToFloat(rawQuatJ, ROTATION_VECTOR_Q1);
    rotation_vector_raw.k = bno080_qToFloat(rawQuatK, ROTATION_VECTOR_Q1);
    rotation_vector_raw.yaw_correction = game_rotation_vector.yaw_correction;//криво
    
    game_rotation_vector = bno080_rotate_quaternion(&rotation_vector_raw);
    game_rotation_vector.accur = bno080_qToFloat(
      rawQuatRadianAccuracy, ROTATION_VECTOR_Q1);
    game_rotation_vector.state = quatAccuracy;
    
    euler_game_rotation_vector = bno080_quat_to_euler(&game_rotation_vector);
    mavlink_send_game_rotation_vector(&euler_game_rotation_vector);
  }
}

//convert quaternion to euler angles
euler_angles_t bno080_quat_to_euler(quaternion_t* quat)
{
  euler_angles_t tmp_euler;
  
  tmp_euler.raw_yaw   =  -atan2f(
    quat->i * quat->j + quat->real * quat->k, 
    (quat->real * quat->real + quat->i * quat->i) - 0.5f) * 
    RADIANS_TO_DEGREES_MULTIPLIER;
  
  if (tmp_euler.raw_yaw < 0.0f)
  tmp_euler.raw_yaw = 360.0f + tmp_euler.raw_yaw;
  
  tmp_euler.roll = -asinf(
    2.0f * (quat->i * quat->k - quat->real * quat->j)) * 
    RADIANS_TO_DEGREES_MULTIPLIER;
  
  tmp_euler.pitch  =  atan2f(
    quat->real * quat->i + quat->j * quat->k, 
    (quat->real * quat->real + quat->k * quat->k) - 0.5f) * 
    RADIANS_TO_DEGREES_MULTIPLIER;
  
  tmp_euler.accur = quat->accur * RADIANS_TO_DEGREES_MULTIPLIER;
  tmp_euler.state = quat->state;
  
  tmp_euler.yaw = tmp_euler.raw_yaw;
  //add correction
  tmp_euler.yaw+= quat->yaw_correction;
  if (tmp_euler.yaw > 360.0f)
    tmp_euler.yaw = tmp_euler.yaw - 360.0f;
  
  if (tmp_euler.yaw < 0.0f)
    tmp_euler.yaw = 360.0f + tmp_euler.yaw;
  
  return tmp_euler;
}

//translate quaternion to the user axies
quaternion_t bno080_rotate_quaternion(quaternion_t* quat)
{
  quaternion_t new_quat;
  float x = 0.0f;
  float y = SQR2;
  float z = 0.0f;
  float w = SQR2;
  
  new_quat.real = quat->real * w - quat->i * x - quat->j * y - quat->k * z;
  new_quat.i = quat->real * x + quat->i * w + quat->j * z - quat->k * y;
  new_quat.j = quat->real * y - quat->i * z + quat->j * w + quat->k * x;
  new_quat.k = quat->real * z + quat->i * y - quat->j * x + quat->k * w;
  
  new_quat.yaw_correction = quat->yaw_correction;
      
  return new_quat;
}

//convert to float
float bno080_qToFloat(int16_t fixedPointValue, uint8_t qPoint)
{
  float qFloat = (float)fixedPointValue;
  qFloat *= powf(2, (float)qPoint * -1.0);
  return (qFloat);
}

void bno080_set_yaw_correction(uint8_t vector_type, float value)
{
  if (vector_type == 0)
    rotation_vector.yaw_correction = value;
  else if (vector_type == 1)
    game_rotation_vector.yaw_correction = value;
  else if (vector_type == 255)
  {
    bno080_real_correction_angle = value;
    bno080_set_yaw_correction_by_real_angle(bno080_real_correction_angle);
  }
}

void bno080_set_yaw_correction_by_real_angle(float real_angle)
{
    float rot_vect_corr = real_angle - euler_rotation_vector.raw_yaw;
    float game_rot_vect_corr = real_angle - euler_game_rotation_vector.raw_yaw;
    
    rotation_vector.yaw_correction = rot_vect_corr;
    game_rotation_vector.yaw_correction = game_rot_vect_corr;
}