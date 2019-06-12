#ifndef __STM32F4_DEMO_H
#define __STM32F4_DEMO_H

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <intrinsics.h>

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
extern volatile uint32_t ms_tick;


#define ABS(x)         (x < 0) ? (-x) : x
#define MAX(a,b)       (a < b) ? (b) : a

#define START_TIMER(x, duration)  (x = (ms_tick + duration))
#define TIMER_ELAPSED(x)  ((ms_tick > x) ? 1 : 0)

#if defined ( __ICCARM__ ) // IAR
    #define ENTER_CRITICAL(x)       x=__get_interrupt_state(); __disable_interrupt()
    #define LEAVE_CRITICAL(x)       __set_interrupt_state(x)

#elif defined (__CC_ARM) // KEIL
    #define ENTER_CRITICAL(x)       x=__disable_irq()
    #define LEAVE_CRITICAL(x)       if (!x) __enable_irq()
    #define NO_INIT                 __attribute__((zero_init))
#else
  #error ERROR
#endif

/* Exported functions ------------------------------------------------------- */
void Delay_ms(uint32_t ms);
#endif
