#ifndef __LS_H__
#define __LS_H__

#include "../Shell/utils.h"
#include <dirent.h>

void ls(char *args);
void list_names(char *path, bool include_hidden_files, bool details);
void print_name(char *name, bool details);
void list_details(char *name);
char *month_name(int month);

#endif
