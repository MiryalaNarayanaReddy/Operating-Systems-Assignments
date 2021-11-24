#include "user.h"
#include <signal.h>

int zone_H_limit;
int zone_A_limit;
int zone_N_limit;

int num_persons_zone_H;
pthread_mutex_t zone_H_cnt_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t zone_H_cnt_cond =  PTHREAD_COND_INITIALIZER;

int num_persons_zone_A;
pthread_mutex_t zone_A_cnt_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t zone_A_cnt_cond =  PTHREAD_COND_INITIALIZER;

int num_persons_zone_N;
pthread_mutex_t zone_N_cnt_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t zone_N_cnt_cond =  PTHREAD_COND_INITIALIZER;

int number_of_goal_chances;

int stimer = -1;
int SPECTATING_TIME_X;
int NUMBER_OF_GROUPS;
pthread_mutex_t stimer_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t stimer_cond = PTHREAD_COND_INITIALIZER;
 int number_of_groups;
int home_team_score;
int away_team_score;

int main()
{
    // printf("hello\n");
    init_all_threads();
}
