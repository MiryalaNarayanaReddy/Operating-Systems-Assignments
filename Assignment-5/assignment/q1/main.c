#include "user.h"

extern int stimer;
extern pthread_mutex_t stimer_lock;
extern pthread_cond_t stimer_cond;

int main()
{
    stimer = -1;
    pthread_mutex_init(&stimer_lock, NULL);
    pthread_cond_init(&stimer_cond,NULL);

    pthread_t timer_thread_id;
    pthread_create(&timer_thread_id, NULL, simulate_timer, NULL);

    init_all_threads();
    pthread_join(timer_thread_id, NULL);
}
