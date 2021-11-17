#include "user.h"
#include <signal.h>

int timer = -1;

void increament_timer(int arg)
{
    timer++;
    printf("timer  = %d\n",timer);
}

void start_simulation()
{
    signal(SIGALRM, increament_timer);
    while (true)
    {
        alarm(1);
        pause();
    }
}

int main()
{
    init_all_threads();
    // start_simulation();
}
