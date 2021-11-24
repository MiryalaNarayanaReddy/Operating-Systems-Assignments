#include "zone.h"

bool updated_zone_cnt(int z)
{
    bool flag = false;
    switch (z)
    {
    case ZONE_H:
        pthread_mutex_lock(&zone_H_cnt_lock);
        if (num_persons_zone_H < zone_H_limit)
        {
            flag = true;
            num_persons_zone_H++;
        }
        pthread_mutex_unlock(&zone_H_cnt_lock);
    case ZONE_A:
        pthread_mutex_lock(&zone_A_cnt_lock);
        if (num_persons_zone_A < zone_A_limit)
        {
            flag = true;
            num_persons_zone_A++;
        }
        pthread_mutex_unlock(&zone_A_cnt_lock);
    case ZONE_N:
        pthread_mutex_lock(&zone_N_cnt_lock);
        if (num_persons_zone_N < zone_N_limit)
        {
            flag = true;
            num_persons_zone_N++;
        }
        pthread_mutex_unlock(&zone_N_cnt_lock);
    }
    return flag;
}