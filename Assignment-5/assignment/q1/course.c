#include "course.h"

void *simulate_course(void *course_details)
{
    course *course_x = (course *)course_details;

    // look for TAs
    printf("course %s %f %d %d\n", course_x->name, course_x->interest, course_x->num_labs, course_x->course_max_slot);
}