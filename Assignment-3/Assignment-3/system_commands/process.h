#ifndef __PROCESS_H__
#define __PROCESS_H__

#include "../Shell/utils.h"
#include "../Shell/user.h"

int parent_pid;
int process_no;
void process(char *command, char *args);
int parse_cmd(char *command, char *args, char *argv[10]);
void forground_process(char **argv);
void background_process(char **argv);
void process_status();


void setup_exit();
void exit_status();

#endif