#ifndef __REDIRECT_IO_H__
#define __REDIRECT_IO_H__

#include "../Shell/utils.h"

int stdin_fd_saved;
int stdout_fd_saved;

void init_redirection();
void disable_redirection();
void redirect_input(char *filename);
void redirect_output(char *filename);


#endif