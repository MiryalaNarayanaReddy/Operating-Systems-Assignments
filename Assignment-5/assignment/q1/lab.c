#include "lab.h"

void *simulate_lab(void *lab_details)
{
    lab *lab_x = (lab *)lab_details;
    //  students allocated as TAs to different courses

    printf("lab %s %d %d\n", lab_x->name, lab_x->num_students, lab_x->num_of_times_TA_limit);
}