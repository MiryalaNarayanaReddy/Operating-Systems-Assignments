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
        char temp[MAX_PATH_LEN];
        strcpy(temp, "");

        while (EXECUTABLE_PATH[i] != '\0')
        {
            if (EXECUTABLE_PATH[i] == '/')
            {
                strcat(temp, "../");
            }
            i++;
        }
        strcpy(CURRENT_DIRECTORY_PATH, temp);
    }
    else
    {
        strcpy(CURRENT_DIRECTORY_PATH, &buff[j]);
    }
}