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

#include "student.h"
#include "course.h"
#include "lab.h"
#include "stimer.h"

#define RED_COLOR    "\x1b[31m"
#define GREEN_COLOR  "\x1b[32m"
#define YELLOW_COLOR "\x1b[33m"
#define BLUE_COLOR   "\x1b[34m"
#define PINK_COLOR   "\x1b[35m"
#define CYAN_COLOR   "\x1b[36m"
#define RESET_COLOR  "\x1b[0m"

extern int stimer;
extern pthread_mutex_t stimer_lock;
extern pthread_cond_t stimer_cond;
struct course *course_list;
struct student *student_list;
struct lab *lab_list;

void init_all_threads();

#endif