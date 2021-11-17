#ifndef __STUDENT_H__
#define __STUDENT_H__

#include "user.h"

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
};

typedef struct student student;

int num_students;

extern int stimer;
extern pthread_mutex_t stimer_lock;
extern pthread_cond_t stimer_cond;

void* simulate_student(void*student_details);

#endif