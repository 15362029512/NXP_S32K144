#ifndef _TIMER_H_
#define _TIMER_H_

#include "Cpu.h"

typedef struct
{
    uint16_t cnt;              
    uint8_t  flg;              
} s_timer_t;

typedef enum
{
	timer_10ms = 0,
	timer_50ms = 1,
	timer_100ms = 2,
	timer_500ms = 3,
	timer_max,
}e_timer_index;

extern s_timer_t timer_array[timer_max];


extern void timer_all_init(void);

#define TIMER_500MS_FLG (timer_array[timer_500ms].flg)


#endif 

