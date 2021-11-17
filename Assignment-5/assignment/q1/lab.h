#ifndef __LAB_H__
#define __LAB_H__

struct lab
{
    int lab_id;
    char name[100];
    int num_students;
    int num_of_times_TA_limit;
};

typedef struct lab lab;

struct ta
{
    int num_courses;
    int lab_id;
};

typedef struct ta ta;

#endif