#ifndef __PROCESS_H__
#define __PROCESS_H__

#include "../Shell/utils.h"


int child_process_number;

void process(char *command, char *args);
int parse_cmd(char *command, char *args, char *argv[10]);
void forground_process(char **argv);
void background_process(char **argv);

#endif