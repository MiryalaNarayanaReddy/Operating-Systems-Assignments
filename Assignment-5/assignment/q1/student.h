#ifndef __STUDENT_H__
#define __STUDENT_H__

#include "user.h"

#define MIN_PROB_OF_LIKING_COURSE 0.25

struct student
{
    int number;
    int time;
    double calibre;
    int preference_course_1;
    int preference_course_2;
    int preference_course_3;
    double prob;
    int current_preference;
    pthread_t tid;
    bool in_simulation;
    int preference;
    pthread_mutex_t preference_lock;
    pthread_cond_t preference_cond;
};

typedef struct student student;

int num_students;

extern int stimer;
extern pthread_mutex_t stimer_lock;
extern pthread_cond_t stimer_cond;

void *simulate_student(void *student_details);

#endif