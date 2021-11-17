#include "student.h"

void *simulate_student(void *student_details)
{
    student *student_x = (student *)student_details;

    // register for course
    // wait

    printf("student %d %f %d %d %d %d\n", student_x->number, student_x->calibre,\
     student_x->preference_course_1, student_x->preference_course_2, student_x->preference_course_3,\
      student_x->time);
}