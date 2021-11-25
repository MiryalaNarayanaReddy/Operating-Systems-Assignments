#include "stimer.h"
#include <signal.h>

void increament_timer(int arg)
{
    pthread_mutex_lock(&stimer_lock);
    stimer++;
    pthread_cond_broadcast(&stimer_cond);
    pthread_mutex_unlock(&stimer_lock);
    // printf("timer  = %d\n", stimer);
}

void simulate_timer(int time)
{
    signal(SIGALRM, increament_timer);
    while (stimer <= time)
    {
        alarm(1);
        pause();
    }
}
