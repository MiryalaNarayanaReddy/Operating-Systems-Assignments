#ifndef __HISTORY_H__
#define __HISTORY_H__

#include "../Shell/utils.h"

char history_file_path[1024];
int number_of_lines_in_history;

void history(char *num);
void push_into_history(char *command);

#endif