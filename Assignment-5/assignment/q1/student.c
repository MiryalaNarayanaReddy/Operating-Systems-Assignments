#include "student.h"

void *simulate_student(void *student_details)
{
    student *student_x = (student *)student_details;

    // register for course
    // wait

    pthread_mutex_lock(&stimer_lock);
    while (stimer != student_x->time)
    {
        pthread_cond_wait(&stimer_cond, &stimer_lock);
    }
    pthread_mutex_unlock(&stimer_lock);
    //   printf("student %d time  = %d\n"RESET_COLOR,student_x->number,stimer);

    printf(BLUE_COLOR"Student %d filled in preferences for course registration\n"RESET_COLOR, student_x->number);
    bool selected_permanently = false;
    if (registered_for_course(student_x->preference_course_1)) // this function will wait till a seat is free to be allocated
    {
        printf(BLUE_COLOR"Student %d has been allocated a seat in course %s\n"RESET_COLOR, student_x->number, course_list[student_x->preference_course_1].name);

        // wait for tut to be  over
        pthread_mutex_lock(&course_list[student_x->preference_course_1].tutorial_lock);
        while (course_list[student_x->preference_course_1].tutorial == false)
            pthread_cond_wait(&course_list[student_x->preference_course_1].tutorial_cond, &course_list[student_x->preference_course_1].tutorial_lock);
        while (course_list[student_x->preference_course_1].tutorial == false)
            pthread_cond_wait(&course_list[student_x->preference_course_1].tutorial_cond, &course_list[student_x->preference_course_1].tutorial_lock);
        pthread_mutex_unlock(&course_list[student_x->preference_course_1].tutorial_lock);
        // end of tut

        student_x->prob = student_x->calibre * course_list[student_x->preference_course_1].interest;
        if (student_x->prob < MIN_PROB_OF_LIKING_COURSE)
        {
            printf(BLUE_COLOR"Student %d has withdrawn from course %s\n"RESET_COLOR, student_x->number, course_list[student_x->preference_course_1].name);
        }
        else
        {
            printf(BLUE_COLOR"Student %d has selected course %s permanently\n"RESET_COLOR, student_x->number, course_list[student_x->preference_course_1].name);
            student_x->preference = student_x->preference_course_1;
            selected_permanently = true;
        }
    }

    if (!selected_permanently)
    {
        if (registered_for_course(student_x->preference_course_2)) // this function will wait till a seat is free to be allocated
        {
            printf(BLUE_COLOR"Student %d has been allocated a seat in course %s\n"RESET_COLOR, student_x->number, course_list[student_x->preference_course_2].name);
            // wait for tut to be  over
            pthread_mutex_lock(&course_list[student_x->preference_course_2].tutorial_lock);
            while (course_list[student_x->preference_course_2].tutorial == false)
                pthread_cond_wait(&course_list[student_x->preference_course_2].tutorial_cond, &course_list[student_x->preference_course_2].tutorial_lock);
            while (course_list[student_x->preference_course_2].tutorial == false)
                pthread_cond_wait(&course_list[student_x->preference_course_2].tutorial_cond, &course_list[student_x->preference_course_2].tutorial_lock);
            pthread_mutex_unlock(&course_list[student_x->preference_course_2].tutorial_lock);
            // end of tut
            student_x->prob = student_x->calibre * course_list[student_x->preference_course_2].interest;
            if (student_x->prob < MIN_PROB_OF_LIKING_COURSE)
            {
                printf(BLUE_COLOR"Student %d has withdrawn from course %s\n"RESET_COLOR, student_x->number, course_list[student_x->preference_course_2].name);
            }
            else
            {
                printf(BLUE_COLOR"Student %d has selected course %s permanently\n"RESET_COLOR, student_x->number, course_list[student_x->preference_course_2].name);
                student_x->preference = student_x->preference_course_2;
                selected_permanently = true;
            }
        }
    }
    if (!selected_permanently)
    {
        if (registered_for_course(student_x->preference_course_3)) // this function will wait till a seat is free to be allocated
        {
            printf(BLUE_COLOR"Student %d has been allocated a seat in course %s\n"RESET_COLOR, student_x->number, course_list[student_x->preference_course_3].name);
            // wait for tut to be  over
            pthread_mutex_lock(&course_list[student_x->preference_course_3].tutorial_lock);
            while (course_list[student_x->preference_course_3].tutorial == false)
                pthread_cond_wait(&course_list[student_x->preference_course_3].tutorial_cond, &course_list[student_x->preference_course_3].tutorial_lock);
            while (course_list[student_x->preference_course_3].tutorial == false)
                pthread_cond_wait(&course_list[student_x->preference_course_3].tutorial_cond, &course_list[student_x->preference_course_3].tutorial_lock);
            pthread_mutex_unlock(&course_list[student_x->preference_course_3].tutorial_lock);
            // end of tut
            student_x->prob = student_x->calibre * course_list[student_x->preference_course_3].interest;
            if (student_x->prob < MIN_PROB_OF_LIKING_COURSE)
            {
                printf(BLUE_COLOR"Student %d has withdrawn from course %s\n"RESET_COLOR, student_x->number, course_list[student_x->preference_course_3].name);
            }
            else
            {
                printf(BLUE_COLOR"Student %d has selected course %s permanently\n"RESET_COLOR, student_x->number, course_list[student_x->preference_course_3].name);
                student_x->preference = student_x->preference_course_3;
                selected_permanently = true;
            }
        }
    }
    if (!selected_permanently)
    {
        printf(BLUE_COLOR"Student %d couldn’t get any of his preferred courses\n"RESET_COLOR, student_x->number);
    }
    // printf("student %d %f %d %d %d %d\n"RESET_COLOR, student_x->number, student_x->calibre,\
    //  student_x->preference_course_1, student_x->preference_course_2, student_x->preference_course_3,\
    //   student_x->time);
}
