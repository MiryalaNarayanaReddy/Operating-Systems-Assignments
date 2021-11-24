#ifndef __GOAL_H__
#define __GOAL_H__

#include "user.h"

struct goal
{
    char team;
    int time;
    float probability;
};

typedef struct goal goal;

extern int number_of_goal_chances;
goal *goal_list;

#endif