#ifndef __HISTORY_H__
#define __HISTORY_H__

#include "../Shell/utils.h"

char history_file_path[1024];
int number_of_lines_in_history;

char History[20][1024];

void history(char *num);
void push_into_history(char *command);
void get_line(FILE *fp, char *buf);

#endif