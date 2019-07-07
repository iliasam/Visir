#include "visual_handling.h"
#include "main.h"
#include "lcd_worker.h"
#include "bno080_sensor.h"
#include "bno080_sensor_parsing.h"

// Defines ********************************************************************
#define CENTER_X                43
#define LEFT_BOUNDARY_X         24
#define LRIGHT_BOUNDARY_X       63

#define CENTER_Y                23

#define PIXEL_SIZE_DEG          (0.14375f)//in deg


typedef enum
{
  VISIR_MODE_BASE = 0,
  VISIR_MODE_TARGET1,
} visir_mode_t;

extern euler_angles_t euler_rotation_vector;
extern euler_angles_t euler_game_rotation_vector;//gyro
extern uint8_t hardware_backlight_on;

uint8_t visir_mode_prev = VISIR_MODE_BASE;
uint8_t visir_mode = VISIR_MODE_BASE;

//Visir target pointer - visible mark
float visir_target_ptr_yaw = 50.0f;//deg
float visir_target_ptr_pitch = 0.0f;//deg


// Functions ******************************************************************
void visual_handling_draw_base(void);
void visual_handling_draw_target1(void);

void visual_handling_update(void)
{
  //clear display if mode had changed
  if (visir_mode != visir_mode_prev)
  {
    lcd_full_clear();
  }
  visir_mode_prev = visir_mode;
  

  switch (visir_mode)
  {
    case VISIR_MODE_BASE:
      visual_handling_draw_base();
      break;
      
    case VISIR_MODE_TARGET1:
      visual_handling_draw_target1();
      break;
      
    default:
      visual_handling_draw_base();
  }
  
  lcd_update();
}

void visual_handling_draw_target1(void)
{
  char tmp_str[32];
  
  lcd_clear_framebuffer();
  
  sprintf(tmp_str, "%.1f   ", euler_game_rotation_vector.yaw);
  lcd_draw_string(tmp_str, 34, 35, FONT_SIZE_6, 0);
  //lcd_draw_string(tmp_str, 34, 7, FONT_SIZE_6, 0);
  
  draw_horiz_line(LEFT_BOUNDARY_X, 63, CENTER_Y);
  draw_vert_line(CENTER_X - 1, CENTER_Y - 2, CENTER_Y);
  draw_vert_line(CENTER_X + 1, CENTER_Y - 2, CENTER_Y);

  //get target marker position
  float angular_diff_x = visir_target_ptr_yaw - euler_game_rotation_vector.yaw;//deg
  
  if (angular_diff_x < -180.0f)
    angular_diff_x = 360.0f + angular_diff_x;
  else if (angular_diff_x > 180.0f)
    angular_diff_x = angular_diff_x - 360.0f;
  
  
  float pixel_diff_x = angular_diff_x / PIXEL_SIZE_DEG;
  int16_t pixel_diff_xint = (int16_t)pixel_diff_x;//offset from center
  
  int16_t marker_x_pos = CENTER_X + pixel_diff_xint;
  
  if (marker_x_pos < LEFT_BOUNDARY_X)
  {
    lcd_draw_string("<", LEFT_BOUNDARY_X + 2, CENTER_Y + 3, FONT_SIZE_8, 0);
  }
  else if (marker_x_pos > LRIGHT_BOUNDARY_X)
  {
    lcd_draw_string(">", LRIGHT_BOUNDARY_X - 6, CENTER_Y + 3, FONT_SIZE_8, 0);
  }
  else
  {
    draw_vert_line(marker_x_pos, CENTER_Y, CENTER_Y + 5);//marker
  }
  
}

void visual_handling_draw_base(void)
{
  char tmp_str[32];
  
  lcd_draw_string(" >< ", 28, 17, FONT_SIZE_11, 0);
  
  sprintf(tmp_str, "%.1f   ", euler_game_rotation_vector.yaw);
  lcd_draw_string(tmp_str, 34, 7, FONT_SIZE_6, 0);
  
  //sprintf(tmp_str, "%.1f   ", euler_rotation_vector.yaw);
  sprintf(tmp_str, "%.1f   ", euler_game_rotation_vector.pitch);
  lcd_draw_string(tmp_str, 34, 35, FONT_SIZE_6, 0);
  
  //draw_horiz_line(28, 60, 23);
  //draw_vert_line(CENTER_X, 10, 30);
  //draw_black_line(30);
  
  //DISPLAY BACKLIGHT
  if (hardware_backlight_on)
  {
    lcd_draw_string("B", 25, 20, FONT_SIZE_6, 0);
  }
  else
  {
    lcd_draw_string(" ", 25, 20, FONT_SIZE_6, 0);
  }
}

void visual_handling_set_target_pose(float yaw, float pitch)
{
  visir_target_ptr_yaw = yaw;
  visir_target_ptr_pitch = pitch;
}

void visual_handling_set_mode(uint8_t mode)
{
  visir_mode = mode;
}