#include "person.h"
#include <sys/time.h>
#include <errno.h>

void *simulate_person(void *arg)
{
    person *person_x = (person *)arg;
    pthread_mutex_lock(&stimer_lock);
    while (stimer != person_x->time)
    {
        pthread_cond_wait(&stimer_cond, &stimer_lock);
    }
    pthread_mutex_unlock(&stimer_lock);
    // printf(BLUE_COLOR "person time = %d\n" RESET_COLOR, person_x->time);
    printf(RED_COLOR "%s has reached the stadium\n" RESET_COLOR, person_x->name);

    // // waiting time part near ticket counter
    // struct timespec abs_time;

    // clock_gettime(CLOCK_REALTIME, &abs_time);
    // abs_time.tv_sec += person_x->patience;
    // abs_time.tv_nsec += person_x->patience * 1000000000;
    // // wait for ticket
    // int error;
    // pthread_mutex_lock(&person_x->zone_lock);
    // while (person_x->zone_x == 'X')
    // {
    //     increament_zone_cnt(person_x);
    //     error = pthread_cond_timedwait(&person_x->zone_cond, &person_x->zone_lock, &abs_time);
    // }
    // if (error == ETIMEDOUT)
    // {
    //     printf(PINK_COLOR "Person %s could not get a seat\n" RESET_COLOR, person_x->zone_x, person_x->name);
    // }
    // else
    // {
    //     pthread_mutex_unlock(&person_x->zone_lock);
    //     printf(PINK_COLOR "%s has got a seat in zone %c\n" RESET_COLOR, person_x->zone_x, person_x->name, person_x->zone_x);
    // }

    person_x->start = stimer;
    increament_zone_cnt(person_x);
    if (person_x->got_seat)
    {
        // printf("watching\n");
        person_x->start = stimer;
        person_x->end = person_x->start + SPECTATING_TIME_X;
        pthread_mutex_lock(&stimer_lock);
        while (stimer != person_x->end && !person_x->at_exit_gate)
        {
            pthread_cond_wait(&stimer_cond, &stimer_lock);
        }
        pthread_mutex_unlock(&stimer_lock);
        if (!person_x->at_exit_gate)
        {
            decreament_zone_cnt(person_x);
            person_x->at_exit_gate = true;
            printf(GREEN_COLOR "%s watched the match for %d seconds and is leaving\n" RESET_COLOR, person_x->name, SPECTATING_TIME_X);
        }
    }
}
