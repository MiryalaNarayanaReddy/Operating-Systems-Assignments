#ifndef _ZONE_H_
#define _ZONE_H_


#include "user.h"

extern int zone_H_limit;
extern int zone_A_limit;
extern int zone_N_limit;

extern int num_persons_zone_H;
extern pthread_mutex_t zone_H_cnt_lock;
extern pthread_cond_t zone_H_cnt_cond ;

extern int num_persons_zone_A;
extern pthread_mutex_t zone_A_cnt_lock;
extern pthread_cond_t zone_A_cnt_cond ;

extern int num_persons_zone_N;
extern pthread_mutex_t zone_N_cnt_lock;
extern pthread_cond_t zone_N_cnt_cond ;

enum
{
    ZONE_H,
    ZONE_A,
    ZONE_N
};

#endif
