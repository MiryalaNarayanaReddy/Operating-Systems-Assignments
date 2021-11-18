#include "user.h"
#include <signal.h>

int stimer = -1;
pthread_mutex_t stimer_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t stimer_cond = PTHREAD_COND_INITIALIZER;


int main()
{
    init_all_threads();
}
