#include "cd.h"
#include <string.h>
#include "../Shell/user.h"
#include <unistd.h>

void cd(char *path)
{
    char buff[MAX_PATH_LEN];
    chdir(path);
    getcwd(buff, MAX_PATH_LEN);
    int i = 0, j = 0;
    while (EXECUTABLE_PATH[i] != '\0' && buff[j] != '\0' && EXECUTABLE_PATH[i] == buff[j])
    {
        i++;
        j++;
    }
    if (buff[j] == '\0')
    {
        if (EXECUTABLE_PATH[i] == '\0')
        {
            strcpy(CURRENT_DIRECTORY_PATH, ""); // we are in same directory as executable.
        }
        else
        {
            strcpy(CURRENT_DIRECTORY_PATH, buff); // we are in directory less otherthan executable from home
        }
    }
    else
    {
        strcpy(CURRENT_DIRECTORY_PATH, &buff[j]); //path relative to executable directory
    }
}