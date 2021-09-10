#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include "user.h"
#include "../builtin_commands/cd.h"
#include "../builtin_commands/echo.h"

#define BOLD true
enum
{

    __RED = 31,
    __GREEN = 32,
    __YELLOW = 33,
    __BLUE = 34,
    __PINK = 35
};

void Color_On(int color, bool bold);
void Color_Off();

void clean_input();
void get_string(char *s);
bool AreSame(char *a, char *b);

#endif