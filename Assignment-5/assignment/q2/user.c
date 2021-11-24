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
    // printf("--\n");
    scanf("%d %d %d", &zone_H_limit, &zone_A_limit, &zone_N_limit);
    // printf("%d %d %d", zone_H_limit,zone_A_limit, zone_N_limit);
    //  printf("--\n");
    scanf("%d", &SPECTATING_TIME_X);
    scanf("%d", &number_of_groups);

    // printf("groups = %d\n", number_of_groups);
    //  printf("--alloc\n");

    group_list = (group *)malloc(sizeof(group) * number_of_groups);
    //   sleep(5);
    char ch;
    for (int i = 0; i < number_of_groups; i++)
    {
        scanf("%d", &group_list[i].number_of_persons);
        // printf("i = %d number of person = %d\n", i, group_list[i].number_of_persons);
        group_list[i].people = (person *)malloc(sizeof(person) * group_list[i].number_of_persons);

        for (int j = 0; j < group_list[i].number_of_persons; j++)
        {
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
    simulate_timer(max_time+5);
}
