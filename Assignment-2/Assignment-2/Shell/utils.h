#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include "user.h"
#include "signal_handler.h"
#include "../ls/ls.h"
#include "../builtin_commands/cd.h"
#include "../builtin_commands/echo.h"
#include "../builtin_commands/pwd.h"
#include "../system_commands/process.h"
#include "../system_commands/pinfo.h"
#include "../system_commands/repeat.h"

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
void Bold(bool status);

void clean_input();
void get_string(char *s);
bool AreSame(char *a, char *b);

#endif