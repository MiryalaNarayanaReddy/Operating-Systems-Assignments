#ifndef __USER_H__
#define __USER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#include "student.h"
#include "course.h"
#include "lab.h"
#include "stimer.h"

extern int stimer;
extern pthread_mutex_t stimer_lock;
extern pthread_cond_t stimer_cond;

void Bold(bool status);
void Color_On(int color, bool bold);
void Color_Off();

void init_all_threads();

#endif