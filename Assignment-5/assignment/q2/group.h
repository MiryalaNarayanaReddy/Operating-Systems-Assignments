#ifndef __GROUP_H__
#define __GROUP_H__

#include "user.h"
#include "person.h"

struct group
{
    int number_of_persons;
   struct person *people;
};

typedef struct group group;
group *group_list;

#endif
