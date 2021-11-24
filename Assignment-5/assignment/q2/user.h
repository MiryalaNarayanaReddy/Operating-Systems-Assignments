#ifndef __USER_H__
#define __USER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>

#include "stimer.h"
#include "zone.h"
#include "person.h"
#include "group.h"

#define RED_COLOR "\x1b[31m"
#define GREEN_COLOR "\x1b[32m"
#define YELLOW_COLOR "\x1b[33m"
#define BLUE_COLOR "\x1b[34m"
#define PINK_COLOR "\x1b[35m"
#define CYAN_COLOR "\x1b[36m"
#define RESET_COLOR "\x1b[0m"

extern int SPECTATING_TIME_X;
extern int NUMBER_OF_GROUPS;
extern int stimer;
extern pthread_mutex_t stimer_lock;
extern pthread_cond_t stimer_cond;
extern int number_of_groups;

extern int zone_H_limit;
extern int zone_A_limit;
extern int zone_N_limit;

extern int num_persons_zone_H;
extern pthread_mutex_t zone_H_cnt_lock;
extern pthread_cond_t zone_H_cnt_cond ;

extern int num_persons_zone_A;
extern pthread_mutex_t zone_A_cnt_lock;
extern pthread_cond_t zone_A_cnt_cond ;

extern int num_persons_zone_N;
extern pthread_mutex_t zone_N_cnt_lock;
extern pthread_cond_t zone_N_cnt_cond ;

void init_all_threads();

#endif
