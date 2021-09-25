#include "pwd.h"

void pwd()
{
    char temp[MAX_PATH_LEN];
    getcwd(temp, MAX_PATH_LEN);
    printf("%s\n", temp);
}
