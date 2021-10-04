#ifndef __PIPE_H__
#define __PIPE_H__

#include "../Shell/utils.h"

#define READ_END 0
#define WRITE_END 1

void check_for_pipes(char *args);
void pipe_all(char **cmd);
void strip_spaces(char *str);

#endif