#ifndef __STIMER_H__
#define __STIMER_H__

#include <iostream>
#include <ctime>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

using namespace std;

extern int stimer;
extern pthread_mutex_t stimer_lock;
extern pthread_cond_t stimer_cond;

void increament_timer(int arg);
void simulate_timer(int time);

#endif