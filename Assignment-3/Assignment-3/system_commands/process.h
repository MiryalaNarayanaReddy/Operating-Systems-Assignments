#ifndef __PROCESS_H__
#define __PROCESS_H__

#include "../Shell/utils.h"
#include "../Shell/user.h"

int parent_pid;
int number_of_children;
pid_t child_processes[100];
char child_process_name[100][100];

void process(char *command, char *args);
int parse_cmd(char *command, char *args, char *argv[10]);
void forground_process(char **argv);
void background_process(char **argv);
void process_status();

#endif