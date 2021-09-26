#ifndef __REDIRECT_IO_H__
#define __REDIRECT_IO_H__

#include "../Shell/utils.h"
#include "../Shell/user.h"

typedef int Command;

void Redirection(Command command, char *cmnd, char *args);
void redirect_input(char *filename);
void redirect_output(char *filename);

#endif