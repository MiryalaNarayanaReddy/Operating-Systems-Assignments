#ifndef __COURSE_H__
#define __COURSE_H__

#include "user.h"

struct course
{
    char name[100];
    double interest;
    int num_labs;
    int lab_ids[50];
    int course_max_slot;

    pthread_t tid;

    int student_cnt;
    pthread_mutex_t student_cnt_lock;
    pthread_cond_t student_cnt_cond;

    int tutorial;
    pthread_mutex_t tutorial_lock;
    pthread_cond_t tutorial_cond;

    bool in_simulation;
    pthread_mutex_t course_exit_lock;
    pthread_cond_t course_exit_cond;

};

typedef struct course course;

int num_courses;

extern int stimer;
extern pthread_mutex_t stimer_lock;
extern pthread_cond_t stimer_cond;

void *simulate_course(void *course_details);
bool registered_for_course(int i);

#endif
