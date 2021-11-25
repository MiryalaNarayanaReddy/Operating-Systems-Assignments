#ifndef __GOAL_H__
#define __GOAL_H__

#include "user.h"

#define GOAL_PROBABILITY 0.5

struct goal
{
    char team;
    int time;
    float probability;
    pthread_t tid;
};

typedef struct goal goal;

extern int number_of_goal_chances;
goal *goal_list;

extern int home_team_score;
extern int away_team_score;

void *simulate_goal(void *arg);

#endif