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
    //   printf("student %d time  = %d\n",student_x->number,stimer);
    printf("Student %d filled in preferences for course registration\n", student_x->number);

    pthread_exit(NULL);

    // printf("student %d %f %d %d %d %d\n", student_x->number, student_x->calibre,\
    //  student_x->preference_course_1, student_x->preference_course_2, student_x->preference_course_3,\
    //   student_x->time);
}
