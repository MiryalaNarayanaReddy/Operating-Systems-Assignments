#include "user.h"

int encode_zone(char ch)
{
    if (ch == 'H')
    {
        return ZONE_H;
    }
    else if (ch == 'A')
    {
        return ZONE_A;
    }
    else if (ch == 'N')
    {
        return ZONE_N;
    }
}

void init_all_threads()
{
    int max_time = 0;
    home_team_score = 0;
    away_team_score = 0;
    num_exited_groups = 0;
    // printf("--\n");
    scanf("%d %d %d", &zone_H_limit, &zone_A_limit, &zone_N_limit);
    // printf("%d %d %d", zone_H_limit,zone_A_limit, zone_N_limit);
    //  printf("--\n");
    scanf("%d", &SPECTATING_TIME_X);
    scanf("%d", &NUMBER_OF_GROUPS);

    // printf("groups = %d\n", NUMBER_OF_GROUPS);
    //  printf("--alloc\n");

    group_list = (group *)malloc(sizeof(group) * NUMBER_OF_GROUPS);
    //   sleep(5);
    char ch;
    for (int i = 0; i < NUMBER_OF_GROUPS; i++)
    {
        scanf("%d", &group_list[i].number_of_persons);
        // printf("i = %d number of person = %d\n", i, group_list[i].number_of_persons);
        group_list[i].people = (person *)malloc(sizeof(person) * group_list[i].number_of_persons);

        //******************* BONUS PART
        group_list[i].num_people_waiting_at_exit = 0;
        pthread_mutex_init(&group_list[i].wait_exit_lock, NULL);
        pthread_cond_init(&group_list[i].wait_exit_cond, NULL);
        group_list[i].number = i;
        //******************** BONUS

        for (int j = 0; j < group_list[i].number_of_persons; j++)
        {
            pthread_mutex_init(&group_list[i].people->zone_lock, NULL);
            pthread_cond_init(&group_list[i].people->zone_cond, NULL);
            group_list[i].people[j].zone_x = 'X';
            group_list[i].people[j].at_exit_gate = false;
            group_list[i].people[j].group = i;
            // printf("done-%d\n", j);
            scanf("%s %c %d %d %d", group_list[i].people[j].name, &ch, &group_list[i].people[j].time, &group_list[i].people[j].patience, &group_list[i].people[j].num_goals_to_enrage);
            // printf("%s %c %d %d %d\n", group_list[i].people[j].name, ch, group_list[i].people[j].time, group_list[i].people[j].patience, group_list[i].people[j].num_goals_to_enrage);
            group_list[i].people[j].fan_type = encode_zone(ch);
            pthread_create(&group_list[i].people[j].tid, NULL, simulate_person, &group_list[i].people[j]);
            if (group_list[i].people[j].time > max_time)
            {
                max_time = group_list[i].people[j].time;
            }
        }
        // BONUS PART
        pthread_create(&group_list[i].tid, NULL, simulate_group, &group_list[i]);
        // BONUS
    }
    scanf("%d\n", &number_of_goal_chances);
    //  printf("num  goals = %d\n",number_of_goal_chances);
    goal_list = (goal *)malloc(sizeof(goal) * number_of_goal_chances);
    for (int i = 0; i < number_of_goal_chances; i++)
    {
        scanf("%c %d %f\n", &goal_list[i].team, &goal_list[i].time, &goal_list[i].probability);
        //  printf("%c %d %f\n", goal_list[i].team, goal_list[i].time, goal_list[i].probability);
        // simulate goals
        pthread_create(&goal_list[i].tid, NULL, simulate_goal, &goal_list[i]);
    }
    // printf("done-\n");
    simulate_timer(); // last persons arrival time and should be  chosen by cpu to run in +5 sec
    printf(GREEN_COLOR "exiting...\n" RESET_COLOR);
}
