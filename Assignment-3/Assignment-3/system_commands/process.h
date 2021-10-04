#ifndef __PROCESS_H__
#define __PROCESS_H__

#include "../Shell/utils.h"
#include "../Shell/user.h"

void process(char *command, char *args);
int parse_cmd(char *command, char *args, char *argv[10]);
void forground_process(char **argv);
void background_process(char **argv);
void process_status();


void Handel_background_process_exit();
void background_process_exit_message();
int get_id_of_bg_process(int pid);

#endif