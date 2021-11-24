#ifndef __PERSON_H_
#define __PERSON_H_

#include "user.h"

struct person
{
    char name[30];
    int time;
    int group;
    int fan_type;
    int patience;
    int num_goals_to_enrage;
    pthread_t tid;

};

typedef struct person person;

enum
{
    HOME_FAN,
    AWAY_FAN,
    NEUTRAL_FAN
};

void *simulate_person(void *arg);

#endif