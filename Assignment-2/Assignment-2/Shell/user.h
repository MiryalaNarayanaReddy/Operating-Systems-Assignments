#ifndef __USER_H__
#define __USER_H__
#include "utils.h"

#define MAX_PATH_LEN 1024

char EXECUTABLE_PATH[MAX_PATH_LEN];
char CURRENT_DIRECTORY_PATH[MAX_PATH_LEN];
typedef int Command;

enum
{
    __new_line,
    __exit,
    __invalid_command,
    __clear,
    __cd,
    __ls,
};


void prompt();
void Get_Command(char *arguments);
void process_command(char *arguments);
Command encode_command(char *command);
void PerformAction(Command command, char *args);

#endif