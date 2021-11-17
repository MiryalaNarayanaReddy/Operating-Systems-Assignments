#ifndef __USER_H__
#define __USER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

void Bold(bool status);
void Color_On(int color, bool bold);
void Color_Off();

#endif