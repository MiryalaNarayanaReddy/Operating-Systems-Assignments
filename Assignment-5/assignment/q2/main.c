#include "user.h"
#include <signal.h>

int zone_H_limit;
int zone_A_limit;
int zone_N_limit;

int num_persons_zone_H;
int num_persons_zone_A;
int num_persons_zone_N;

int number_of_goal_chances;

int stimer = -1;
int SPECTATING_TIME_X;
int NUMBER_OF_GROUPS;

pthread_mutex_t stimer_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t stimer_cond = PTHREAD_COND_INITIALIZER;

int number_of_groups;
int home_team_score;
int away_team_score;

pthread_mutex_t zone_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t zone_cond = PTHREAD_COND_INITIALIZER;

int main()
{
    // printf("hello\n");
    init_all_threads();
}
