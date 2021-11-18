#include "user.h"

void Bold(bool status)
{
    if (status)
    {
        printf("\e[1m");
    }
    else
    {
        printf("\e[0m");
    }
}

void Color_On(int color, bool bold)
{
    if (bold)
    {
        printf("\033[231;%dm\e[1m", color);
    }
    else
    {
        printf("\033[231;%dm", color);
    }
}

void Color_Off()
{
    printf("\033[m");
}

void init_all_threads()
{
    scanf("%d %d %d", &num_students, &num_labs, &num_courses);

    course_list = (course *)(malloc(sizeof(course) * num_courses));
    student_list = (student *)(malloc(sizeof(student) * num_students));
    lab_list = (lab *)(malloc(sizeof(lab) * num_labs));

    for (int i = 0; i < num_courses; i++)
    {
        pthread_mutex_init(&course_list[i].student_cnt_lock, NULL);
        pthread_cond_init(&course_list[i].student_cnt_cond, NULL);

        scanf("%s %lf %d %d", course_list[i].name, &course_list[i].interest, &course_list[i].course_max_slot, &course_list[i].num_labs);
        for (int j = 0; j < course_list[i].num_labs; j++)
        {
            scanf("%d", &course_list[i].lab_ids[j]);
        }
        pthread_create(&course_list[i].tid, NULL, simulate_course, (void *)(&course_list[i]));
    }

    for (int i = 0; i < num_students; i++)
    {
        scanf("%lf %d %d %d %d", &student_list[i].calibre, &student_list[i].preference_course_1, &student_list[i].preference_course_2, &student_list[i].preference_course_3, &student_list[i].time);
        student_list[i].number = i;
        pthread_create(&student_list[i].tid, NULL, simulate_student, (void *)(&student_list[i]));
    }

    for (int i = 0; i < num_labs; i++)
    {
        scanf("%s %d %d", lab_list[i].name, &lab_list[i].num_students, &lab_list[i].num_of_times_TA_limit);

        lab_list[i].student_ta = (ta *)malloc(sizeof(ta) * lab_list[i].num_students);
        for (int j = 0; j < lab_list[i].num_students; j++)
        {
            lab_list[i].student_ta[j].num_courses = 0;
            lab_list[i].student_ta[j].is_free = true;
        }
    }

    simulate_timer(num_students+1);

    for (int i = 0; i < num_courses; i++)
    {
        pthread_join(course_list[i].tid, NULL);
    }
    for (int i = 0; i < num_students; i++)
    {
        pthread_join(student_list[i].tid, NULL);
    }

}
