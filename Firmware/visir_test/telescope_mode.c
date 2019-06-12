//AZ_to_EQ code is taken from here: https://www.instructables.com/id/Control-Your-Telescope-Using-Stellarium-Arduino/
/* Includes ------------------------------------------------------------------*/
#include "telescope_mode.h"
#include "main.h"
#include "string.h"
#include "bluetooth_comm.h"
#include "bno080_sensor_parsing.h"
#include "math.h"

extern euler_angles_t euler_game_rotation_vector;//gyro

/* Private typedef -----------------------------------------------------------*/
typedef enum 
{
  TELESCOPE_RX_IDLE = 0,
  TELESCOPE_RX_1,
  TELESCOPE_RX_DATA,
  TELESCOPE_RX_END,
} telescope_rx_state_t;

typedef struct
{
  uint16_t arHH;
  uint16_t arMM;
  uint16_t arSS;
  
  uint8_t pos_sign;
  uint16_t decDEG;
  uint16_t decMM;
  uint16_t decSS;
} equatorial_values_t;

equatorial_values_t equatorial_values;


/* Private define ------------------------------------------------------------*/
#define TELESCOPE_RX_BUF        16
#define M_PI                    3.14159265358

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t telescope_mode_enabled = 0;

char telescope_rx_buf[TELESCOPE_RX_BUF];
uint8_t telescope_rx_pos = 0;

telescope_rx_state_t telescope_rx_state = TELESCOPE_RX_IDLE;

//Converter values
double cos_phi, sin_phi;

/* Private function prototypes -----------------------------------------------*/
void telescope_mode_parse_rx_cmd(void);
void telescope_send_gr(void);
void telescope_send_gd(void);

void telescope_update_equatorial_values(void);
void telescope_init_converter(void);

/* Private functions ---------------------------------------------------------*/

void telescope_mode_switch_mode(void)
{
  telescope_mode_enabled^= 1;
}

//receive "#:GR#" or "#:GD#"
void telescope_mode_parse_byte(uint8_t data)
{
  if (telescope_mode_enabled == 0)
    return;
  
  switch (telescope_rx_state)
  {
    case TELESCOPE_RX_IDLE:
      if (data == '#')
        telescope_rx_state = TELESCOPE_RX_1;
      break;
    
    case TELESCOPE_RX_1:
      if (data == ':')
      {
        telescope_rx_state = TELESCOPE_RX_DATA;
        telescope_rx_pos = 0;
      }
      else
        telescope_rx_state = TELESCOPE_RX_IDLE;
      break;
      
    case TELESCOPE_RX_DATA:
      if (data == '#')
      {
        telescope_rx_state = TELESCOPE_RX_END;
        telescope_mode_parse_rx_cmd();
      }
      else
      {
        if (telescope_rx_pos < sizeof(telescope_rx_buf))
        {
          telescope_rx_buf[telescope_rx_pos] = data;
          telescope_rx_pos++;
        }
        else
          telescope_rx_state = TELESCOPE_RX_IDLE;
      }
      break;
  }
}

void telescope_mode_parse_rx_cmd(void)
{
  if (strncmp(telescope_rx_buf, "GR", 2) == 0)
  {
    telescope_send_gr();
  }
  else if (strncmp(telescope_rx_buf, "GD", 2) == 0)// Telescope Declination
  {
    telescope_send_gd();
  }
  telescope_rx_state = TELESCOPE_RX_IDLE;
}

void telescope_send_gr(void)//RA
{
  static uint8_t tmp_min = 0;
  char tmp_str[20];
  uint16_t size = sprintf(tmp_str, "%02d:%02d:%02d#", 
      equatorial_values.arHH, equatorial_values.arMM, equatorial_values.arSS);
  bluetooth_add_data_for_tx((uint8_t*)tmp_str, size);
  
  tmp_min++;
  if (tmp_min > 59)
    tmp_min = 0;
}

void telescope_send_gd(void)//DEC
{
  char tmp_str[20];
  char sign = '+';
  if (equatorial_values.pos_sign == 0)
    sign = '-';
  
  uint16_t size = sprintf(tmp_str, "%c%02d*%02d:%02d#", sign, 
      equatorial_values.decDEG, equatorial_values.decMM, equatorial_values.decSS);
  bluetooth_add_data_for_tx((uint8_t*)tmp_str, size);
}

void telescope_init_converter(void)
{
  cos_phi = cos((((latHH * 3600) + (latMM * 60) + latSS) / 3600.0) * pi / 180.0);
  sin_phi = sin((((latHH * 3600) + (latMM * 60) + latSS) / 3600.0) * pi / 180.0);
}

void telescope_update_equatorial_values(void)
{
  double delta_tel, sin_h, cos_h, sin_A, cos_A, sin_DEC, cos_DEC;
  double H_telRAD, h_telRAD, A_telRAD;
  long H_tel;
  long arHH, arMM, arSS;
  long decDEG, decMM, decSS;
  char sDEC_tel;

  A_telRAD = euler_game_rotation_vector.yaw;
  h_telRAD = euler_game_rotation_vector.pitch;
  sin_h = sin(h_telRAD);
  cos_h = cos(h_telRAD);
  sin_A = sin(A_telRAD);
  cos_A = cos(A_telRAD);
  delta_tel = asin((sin_phi * sin_h) + (cos_phi * cos_h * cos_A));
  sin_DEC = sin(delta_tel);
  cos_DEC = cos(delta_tel);
  DEC_tel_s = long((delta_tel * 180.0 / M_PI) * 3600.0);

  while (DEC_tel_s >= 324000) {
    DEC_tel_s = DEC_tel_s - 324000;
  }
  while (DEC_tel_s <= -324000) {
    DEC_tel_s = DEC_tel_s + 324000;
  }

  H_telRAD = acos((sin_h - (sin_phi * sin_DEC)) / (cos_phi * cos_DEC));
  H_tel = long((H_telRAD * 180.0 / M_PI) * 240.0);

  if (sin_A >= 0) {
    H_tel = 86400 - H_tel;
  }
  AR_tel_s = TSL - H_tel;

  while (AR_tel_s >= 86400) {
    AR_tel_s = AR_tel_s - 86400;
  }
  while (AR_tel_s < 0) {
    AR_tel_s = AR_tel_s + 86400;
  }

  arHH = AR_tel_s / 3600;
  arMM = (AR_tel_s - arHH * 3600) / 60;
  arSS = (AR_tel_s - arHH * 3600) - arMM * 60;
  decDEG = abs(DEC_tel_s) / 3600;
  decMM = (abs(DEC_tel_s) - decDEG * 3600) / 60;
  decSS = (abs(DEC_tel_s) - decDEG * 3600) - decMM * 60;
  
  //set sign
  if (DEC_tel_s < 0)
    equatorial_values.pos_sign = 0;
  else
    equatorial_values.pos_sign = 1;
  
  equatorial_values.arHH = arHH;
  equatorial_values.arMM = arMM;
  equatorial_values.arSS = arSS;
  
  equatorial_values.decDEG = decDEG;
  equatorial_values.decMM = decMM;
  equatorial_values.decSS = decSS;
}