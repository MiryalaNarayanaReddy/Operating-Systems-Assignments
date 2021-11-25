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
        if (home_team_score > away_team_score)
        {
            int difference = home_team_score - away_team_score;
            for (int i = 0; i < NUMBER_OF_GROUPS; i++)
            {
                for (int j = 0; j < group_list[i].number_of_persons; j++)
                {
                    if (group_list[i].people[j].in_stadium && group_list[i].people[j].fan_type == AWAY_FAN && difference >= group_list[i].people[j].num_goals_to_enrage)
                    {
                        group_list[i].people[j].at_exit_gate = true;
                        printf(GREEN_COLOR "%s is leaving due to bad performance of his team\n" RESET_COLOR, group_list[i].people[j].name);
                    }
                }
            }
        }
        else if (home_team_score < away_team_score)
        {
            int difference = away_team_score - home_team_score;
            for (int i = 0; i < NUMBER_OF_GROUPS; i++)
            {
                for (int j = 0; j < group_list[i].number_of_persons; j++)
                {
                    if (group_list[i].people[j].in_stadium && group_list[i].people[j].fan_type == HOME_FAN && difference >= group_list[i].people[j].num_goals_to_enrage)
                    {
                        group_list[i].people[j].at_exit_gate = true;
                        printf(GREEN_COLOR "%s is leaving due to bad performance of his team\n" RESET_COLOR, group_list[i].people[j].name);
                    }
                }
            }
        }
    }
    else
    {
        printf("Team %c missed the chance to score their goal number %d\n", goal_x->team, (goal_x->team == 'H' ? home_team_score : away_team_score) + 1);
    }
}