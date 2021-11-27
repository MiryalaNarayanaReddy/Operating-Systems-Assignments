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
    int cnt = 0;
    while (stimer <= time)
    {
        alarm(1);
        pause();
        for (int i = 0; i < num_students; i++)
        {
            if ((!student_list[i].in_simulation) || student_list[i].selected_permanently)
            {
                cnt++;
            }
        }
        if (cnt == num_students)
        {
            sleep(2);
            cnt = 2;
            for (int i = 0; i < num_students; i++)
            {
                if ((!student_list[i].in_simulation) || student_list[i].selected_permanently)
                {
                    cnt++;
                }
            }
            break;
        }
        else
        {
            cnt = 0;
        }
    }
}
