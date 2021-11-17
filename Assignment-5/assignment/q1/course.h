#ifndef __COURSE_H__
#define __COURSE_H__

#include "user.h"

struct course{
    char name[100];
    double interest;
    int num_labs;
    int lab_ids[50];
    int course_max_slot;
};

typedef struct course course;

int num_courses;

extern int stimer;
extern pthread_mutex_t stimer_lock;
extern pthread_cond_t stimer_cond;

void *simulate_course(void *course_details);

#endif