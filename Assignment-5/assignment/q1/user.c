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

    pthread_t course_thread_ids[num_courses];
    pthread_t student_thread_ids[num_students];
    pthread_t lab_thread_ids[num_labs];

    for (int i = 0; i < num_courses; i++)
    {
        pthread_t current_course_tid;
        course *current_course = (course *)(malloc(sizeof(course)));
        scanf("%s %lf %d %d", current_course->name, &current_course->interest, &current_course->course_max_slot, &current_course->num_labs);
        for (int j = 0; j < current_course->num_labs; j++)
        {
            scanf("%d", &current_course->lab_ids[j]);
        }
        pthread_create(&current_course_tid, NULL, simulate_course, (void *)(current_course));
        course_thread_ids[i] = current_course_tid;
    }

    for (int i = 0; i < num_students; i++)
    {
        pthread_t current_student_tid;
        student *current_student = (student *)(malloc(sizeof(student)));
        scanf("%lf %d %d %d %d", &current_student->calibre, &current_student->preference_course_1, &current_student->preference_course_2, &current_student->preference_course_3, &current_student->time);
        current_student->number = i;
        pthread_create(&current_student_tid, NULL, simulate_student, (void *)(current_student));
        student_thread_ids[i] = current_student_tid;
    }

    for (int i = 0; i < num_labs; i++)
    {
        pthread_t current_lab_tid;
        lab *current_lab = (lab *)malloc(sizeof(lab));
        scanf("%s %d %d", current_lab->name, &current_lab->num_students, &current_lab->num_of_times_TA_limit);

        current_lab->student_ta = (ta *)malloc(sizeof(ta) * current_lab->num_students);
        for (int j = 0; j < current_lab->num_students; j++)
        {
            current_lab->student_ta[j].num_courses = 0;
        }
        pthread_create(&current_lab_tid, NULL, simulate_lab, (void *)(current_lab));
        lab_thread_ids[i] = current_lab_tid;
    }
    
    // pthread_mutex_lock(&start_clock_lock);
    // start_clock = true;
    // pthread_cond_signal(&start_clock_cond);
    // pthread_mutex_unlock(&start_clock_lock);
    simulate_timer(5);



    for (int i = 0; i < num_courses; i++)
    {
        pthread_join(course_thread_ids[i], NULL);
    }
    for (int i = 0; i < num_students; i++)
    {
        pthread_join(student_thread_ids[i], NULL);
    }
    for (int i = 0; i < num_labs; i++)
    {
        pthread_join(lab_thread_ids[i], NULL);
    }

    exit(0);
}
