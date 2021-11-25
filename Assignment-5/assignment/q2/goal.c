#include "goal.h"

void *simulate_goal(void *arg)
{
    goal *goal_x = (goal *)arg;
    pthread_mutex_lock(&stimer_lock);
    while (stimer != goal_x->time)
    {
        pthread_cond_wait(&stimer_cond, &stimer_lock);
    }
    pthread_mutex_unlock(&stimer_lock);

    if (goal_x->probability >= GOAL_PROBABILITY)
    {
        if (goal_x->team == 'H')
        {
            home_team_score++;
            printf("Team %c has scored their goal number %d\n", goal_x->team, home_team_score);
        }
        else
        { // goal_x->team == 'A'
            away_team_score++;
            printf("Team %c has scored their goal number %d\n", goal_x->team, away_team_score);
        }
        // check for enraged spectators
    }
    else
    {
        printf("Team %c missed the chance to score their goal number %d\n", goal_x->team, (goal_x->team == 'H' ? home_team_score : away_team_score) + 1);
    }
}