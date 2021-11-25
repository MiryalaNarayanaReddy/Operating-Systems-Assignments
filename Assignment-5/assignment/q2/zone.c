#include "zone.h"
#include "person.h"

void increament_zone_cnt(person *p) // use first come first serve
{
    // printf("--%c--\n",p->zone_x);
    pthread_mutex_lock(&zone_lock);
    pthread_mutex_lock(&p->zone_lock);
    p->end = stimer;
    switch (p->fan_type)
    {
    case HOME_FAN:
        if (num_persons_zone_H < zone_H_limit)
        {
            p->zone_x = 'H';
            num_persons_zone_H++;
        }
        else if (num_persons_zone_N < zone_N_limit)
        {
            p->zone_x = 'N';
            num_persons_zone_N++;
        }
        break;
    case AWAY_FAN:
        if (num_persons_zone_A < zone_A_limit)
        {
            p->zone_x = 'A';
            num_persons_zone_A++;
        }
        break;
    case NEUTRAL_FAN:
        if (num_persons_zone_H < zone_H_limit)
        {
            p->zone_x = 'H';
            num_persons_zone_H++;
        }
        else if (num_persons_zone_A < zone_A_limit)
        {
            p->zone_x = 'A';
            num_persons_zone_A++;
        }
        else if (num_persons_zone_N < zone_N_limit)
        {
            p->zone_x = 'N';
            num_persons_zone_N++;
        }
        break;
    }
    // sleep(3);

    if (p->zone_x != 'X' && (p->end - p->start) <= p->patience)
    {
        p->got_seat = true;
        printf(PINK_COLOR "%s has got a seat in zone %c\n" RESET_COLOR, p->name, p->zone_x);
    }
    else
    {
        if (p->zone_x == 'H')
        {
            num_persons_zone_H--;
        }
        else if (p->zone_x == 'A')
        {
            num_persons_zone_A--;
        }
        else if (p->zone_x == 'N')
        {
            num_persons_zone_N--;
        }
        printf(PINK_COLOR "%s could not get a seat\n" RESET_COLOR, p->name);
    }
    pthread_mutex_unlock(&p->zone_lock);
    pthread_mutex_unlock(&zone_lock);
}

void decreament_zone_cnt(person *p) // use first come first serve
{
    pthread_mutex_lock(&zone_lock);

    switch (p->zone_x)
    {
    case 'H':
        if (num_persons_zone_H < zone_H_limit)
        {
            num_persons_zone_H--;
        }
        break;
    case 'A':
        if (num_persons_zone_A < zone_A_limit)
        {
            num_persons_zone_A--;
        }
        break;
    case 'N':
        if (num_persons_zone_N < zone_N_limit)
        {
            num_persons_zone_N--;
        }
        break;
    }
    pthread_mutex_unlock(&zone_lock);
}
