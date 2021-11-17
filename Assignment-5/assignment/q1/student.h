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

void* simulate_student(void*student_details);

#endif