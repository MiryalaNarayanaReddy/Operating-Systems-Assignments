#include "user.h"

int timer = -1;
pthread_mutex_t timer_lock;

void *increment_timer(void *arg)
{
    pthread_mutex_lock(&timer_lock);
    timer++;
    pthread_mutex_unlock(&timer_lock);
    return NULL;
}

int main()
{
    pthread_mutex_init(&timer_lock,NULL);


    
    pthread_mutex_destroy(&timer_lock);

}