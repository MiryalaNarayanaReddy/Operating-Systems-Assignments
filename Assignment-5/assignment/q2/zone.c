#include "zone.h"

int increament_zone_cnt(int fan_type)
{
    bool flag = false;
    switch (fan_type)
    {
    case HOME_FAN:
        pthread_mutex_lock(&zone_H_cnt_lock);
        if (num_persons_zone_H < zone_H_limit)
        {
            flag = true;
            num_persons_zone_H++;
        }
        pthread_mutex_unlock(&zone_H_cnt_lock);
    case AWAY_FAN:
        pthread_mutex_lock(&zone_A_cnt_lock);
        if (num_persons_zone_A < zone_A_limit)
        {
            flag = true;
            num_persons_zone_A++;
        }
        pthread_mutex_unlock(&zone_A_cnt_lock);
    case NEUTRAL_FAN:
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

int decreament_zone_cnt(int fan_type)
{
    bool flag = false;
    switch (fan_type)
    {
    case HOME_FAN:
        pthread_mutex_lock(&zone_H_cnt_lock);
        if (num_persons_zone_H > 0)
        {
            flag = true;
            num_persons_zone_H--;
        }
        pthread_mutex_unlock(&zone_H_cnt_lock);
    case AWAY_FAN:
        pthread_mutex_lock(&zone_A_cnt_lock);
        if (num_persons_zone_A > 0)
        {
            flag = true;
            num_persons_zone_A--;
        }
        pthread_mutex_unlock(&zone_A_cnt_lock);
    case NEUTRAL_FAN:
        pthread_mutex_lock(&zone_N_cnt_lock);
        if (num_persons_zone_N > 0)
        {
            flag = true;
            num_persons_zone_N--;
        }
        pthread_mutex_unlock(&zone_N_cnt_lock);
    }
    return flag;
}