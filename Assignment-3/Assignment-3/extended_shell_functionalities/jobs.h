#ifndef __JOBS_H__
#define __JOBS_H__

#include "../Shell/utils.h"

int num_jobs;
int current_fg;

struct processes
{
    char name[20];
    pid_t pid;
};

struct  processes jobs[30];

void list_jobs(char *args);
void push_into_jobs(char *p, int pid);

#endif