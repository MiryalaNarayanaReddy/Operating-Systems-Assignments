#include "course.h"

bool registered_for_course(int i)
{
    bool flag = false;
    pthread_mutex_lock(&course_list[i].student_cnt_lock);
    if (course_list[i].student_cnt < course_list[i].course_max_slot)
    {
        course_list[i].student_cnt++;
        pthread_cond_signal(&course_list[i].student_cnt_cond);
        flag = true;
    }
    pthread_mutex_unlock(&course_list[i].student_cnt_lock);
    return flag;
}

void withdrawn_from_course(int i)
{
    pthread_mutex_lock(&course_list[i].student_cnt_lock);
    if (course_list[i].student_cnt > 0)
    {
        course_list[i].student_cnt--;
        pthread_cond_signal(&course_list[i].student_cnt_cond);
    }
    pthread_mutex_unlock(&course_list[i].student_cnt_lock);
}

void *simulate_course(void *course_details)
{
    course *course_x = (course *)course_details;

    pthread_mutex_lock(&stimer_lock);
    while (stimer == -1)
    {
        pthread_cond_wait(&stimer_cond, &stimer_lock);
    }
    pthread_mutex_unlock(&stimer_lock);

    printf(GREEN_COLOR "Course %s has been allocated %d seats\n" RESET_COLOR, course_x->name, course_x->course_max_slot);

    pthread_mutex_lock(&course_x->student_cnt_lock);
    while (course_x->student_cnt == 0)
    {
        pthread_cond_wait(&course_x->student_cnt_cond, &course_x->student_cnt_lock);
    }
    pthread_mutex_unlock(&course_x->student_cnt_lock);

    // look for TAs
    int ta_num;
    int ta_lab;
    while (true)
    {
        // bool new_student_added = false;
        bool found_ta = false;

        // int num_stds = course_x->student_cnt;
        for (int i = 0; i < course_x->num_labs; i++)
        {
            lab *lab_x = &lab_list[i];
            for (int j = 0; j < lab_x->num_students; j++)
            {
                // use semaphore / mutex locks or thread to update the ta allocation
                pthread_mutex_lock(&lab_x->student_ta[j].ta_lock);
                if (lab_x->student_ta[j].is_free && (lab_x->student_ta[j].num_courses < lab_x->num_of_times_TA_limit))
                {
                    lab_x->student_ta[j].is_free = false;
                    lab_x->student_ta[j].num_courses++;
                    found_ta = true;
                    ta_num = j;
                    ta_lab = i;
                    printf(PINK_COLOR "TA %d from lab %s has been allocated to course %s for his TA ship number  %d\n" RESET_COLOR, j, lab_x->name, course_x->name, lab_x->student_ta[j].num_courses);
                    pthread_mutex_unlock(&lab_x->student_ta[j].ta_lock);
                    break;
                }
                pthread_mutex_unlock(&lab_x->student_ta[j].ta_lock);
            }
        }
        if (!found_ta)
        {
            // have to do some more work.....
            course_x->in_simulation = false;
            printf(RED_COLOR "Course %s does not have any TA mentors eligible and is removed from course offerings\n" RESET_COLOR, course_x->name);
            pthread_mutex_lock(&course_x->course_exit_lock);
            pthread_cond_broadcast(&course_x->course_exit_cond);
            pthread_mutex_unlock(&course_x->course_exit_lock);
            // remove the course from the list and exit thread
            break;
        }

        // conduct tutorial
        pthread_mutex_lock(&course_x->tutorial_lock);
        course_x->tutorial = true;
        pthread_cond_broadcast(&course_x->tutorial_cond);
        printf(PINK_COLOR "Tutorial has started for Course %s with %d seats filled out of %d\n" RESET_COLOR, course_x->name, course_x->student_cnt, course_x->course_max_slot);
        sleep(1);
        lab_list[ta_lab].student_ta[ta_num].is_free = true;
        pthread_mutex_unlock(&course_x->tutorial_lock);
        printf(PINK_COLOR "TA %d from lab %s has completed the tutorial for the course %s\n" RESET_COLOR, ta_num, lab_list[ta_lab].name, course_x->name);

        pthread_mutex_lock(&course_x->student_cnt_lock);
        pthread_cond_wait(&course_x->student_cnt_cond, &course_x->student_cnt_lock);
        pthread_mutex_unlock(&course_x->student_cnt_lock);
    }
    // allow students to register
    // printf(GREEN_COLOR"course %s %f %d %d\n"RESET_COLOR, course_x->name, course_x->interest, course_x->num_labs, course_x->course_max_slot);

    // conduct tutorial.
}