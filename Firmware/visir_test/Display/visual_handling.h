#ifndef VISUAL_HANDLING_H
#define VISUAL_HANDLING_H

#include <stdint.h>

// Defines ********************************************************************


// Functions ******************************************************************
void visual_handling_update(void);
void visual_handling_set_target_pose(float yaw, float pitch);
void visual_handling_set_mode(uint8_t mode);


#endif
