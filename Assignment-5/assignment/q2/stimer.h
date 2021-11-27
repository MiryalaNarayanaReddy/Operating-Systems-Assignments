#ifndef __STIMER_H__
#define __STIMER_H__

#include "user.h"


extern pthread_mutex_t stimer_lock ;
extern pthread_cond_t stimer_cond;

extern bool start_clock;
extern pthread_mutex_t start_clock_lock;
extern pthread_cond_t start_clock_cond;

void increament_timer(int arg);
void simulate_timer();

#endif