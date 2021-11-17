#ifndef __STIMER_H__
#define __STIMER_H__

#include "user.h"


pthread_mutex_t stimer_lock;
pthread_cond_t stimer_cond;
void increament_timer(int arg);
void simulate_timer();

#endif