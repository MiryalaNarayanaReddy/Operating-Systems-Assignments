#ifndef __USER_H__
#define __USER_H__

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define MAX_PATH_LEN 1024

char EXECUTABLE_PATH[MAX_PATH_LEN];
char CURRENT_DIRECTORY_PATH[MAX_PATH_LEN];
typedef int Command;

enum
{
    __RED = 31,
    __GREEN = 32,
    __YELLOW = 33,
    __BLUE = 34,
    __PINK = 35
};

enum
{
    __new_line,
    __cd,
    __ls,
};

void Bold(bool state);
void Color_On(int color);
void Color_Off();

void prompt();
void clean_input();
void get_string(char *s);
bool AreSame(char *a, char *b);
Command Get_Command();
void PerformAction(Command command);

#endif