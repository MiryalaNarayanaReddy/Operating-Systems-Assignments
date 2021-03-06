#ifndef __LAB_H__
#define __LAB_H__

#include "user.h"

struct ta
{
    int num_courses;
    bool is_free;
    pthread_mutex_t ta_lock;
    pthread_cond_t ta_cond;
};

typedef struct ta ta;

struct lab
{
    int lab_id;
    char name[100];
    int num_students;
    ta *student_ta;
    int num_of_times_TA_limit;
};

typedef struct lab lab;
int num_labs;

extern int stimer;
extern pthread_mutex_t stimer_lock;
extern pthread_cond_t stimer_cond;

#endif