#ifndef __USER_H__
#define __USER_H__
#include "utils.h"

#define MAX_PATH_LEN 1024
#define MAX_ARGS 100

char EXECUTABLE_PATH[MAX_PATH_LEN];
char CURRENT_DIRECTORY_PATH[MAX_PATH_LEN];
char USER_HOME_PATH[MAX_PATH_LEN];
char SAVED_PATH[MAX_PATH_LEN];

typedef int Command;

enum
{
    __new_line,
    __exit,
    __clear,
    __cd,
    __pwd,
    __ls,
    __echo,
    __pinfo,
    __system_process
};


void prompt();
void Get_Command(char *arguments);
void tokenize(char *source, char *dest);
void process_command(char *arguments);
Command encode_command(char *command);
void PerformAction(Command command, char *args);

#endif