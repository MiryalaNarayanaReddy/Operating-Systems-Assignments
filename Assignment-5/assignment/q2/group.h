#ifndef __GROUP_H__
#define __GROUP_H__

#include "user.h"
#include "person.h"

struct group
{
    int number;
    int number_of_persons;
    struct person *people;

    int num_people_waiting_at_exit;
    pthread_mutex_t wait_exit_lock;
    pthread_cond_t wait_exit_cond;
    pthread_t tid;
};

typedef struct group group;
group *group_list;

void *simulate_group(void *arg);
void increament_exiting_cnt(int group_number);

#endif
