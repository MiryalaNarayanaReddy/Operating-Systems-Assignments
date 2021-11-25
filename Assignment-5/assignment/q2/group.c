#include "group.h"

//********************* BONUS PART
void increament_exiting_cnt(int group_number)
{
    pthread_mutex_lock(&group_lock);
    pthread_mutex_lock(&group_list[group_number].wait_exit_lock);
    group_list[group_number].num_people_waiting_at_exit++;
    pthread_cond_signal(&group_list[group_number].wait_exit_cond);
    pthread_mutex_unlock(&group_list[group_number].wait_exit_lock);
    pthread_mutex_unlock(&group_lock);
}

void *simulate_group(void *arg)
{
    group *group_x = (group *)arg;
    pthread_mutex_lock(&stimer_lock);
    while (stimer ==-1)
    {
        pthread_cond_wait(&stimer_cond, &stimer_lock);
    }
    pthread_mutex_unlock(&stimer_lock);
    pthread_mutex_lock(&group_x->wait_exit_lock);
    while (group_x->num_people_waiting_at_exit != group_x->number_of_persons)
    {
        // printf("group %d has %d people at exit\n",group_x->number+1,group_x->num_people_waiting_at_exit);
        pthread_cond_wait(&group_x->wait_exit_cond, &group_x->wait_exit_lock);
    }
    pthread_mutex_unlock(&group_x->wait_exit_lock);
    printf(BLUE_COLOR "Group %d leaving for dinner\n" RESET_COLOR, group_x->number+1);
}

//************ BONUS