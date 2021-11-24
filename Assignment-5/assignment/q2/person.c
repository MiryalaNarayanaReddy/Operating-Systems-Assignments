#include "person.h"

void *simulate_person(void *arg)
{
    person *person_x = (person*)arg;
    pthread_mutex_lock(&stimer_lock);
    while (stimer != person_x->time)
    {
        pthread_cond_wait(&stimer_cond, &stimer_lock);
    }
    pthread_mutex_unlock(&stimer_lock);
    printf(BLUE_COLOR "person time = %d\n" RESET_COLOR, person_x->time);
}