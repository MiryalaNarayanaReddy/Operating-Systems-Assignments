#ifndef __COURSE_H__
#define __COURSE_H__

struct course{
    char name[100];
    double interest;
    int num_labs;
    int lab_ids[50];
    int course_max_slot;
};

typedef struct course course;

int num_courses;


#endif