#include "cd.h"

void cd(char *path)
{
    char buff[MAX_PATH_LEN];
    char temp[MAX_PATH_LEN];
    getcwd(temp, MAX_PATH_LEN); // contains current working directory path

    int test = chdir(path); //returns 1 if it fails

    if (test)
    {
        if (AreSame(path, "-"))
        {
            if (!changed_path)
            {
                printf("No saved old working directory\n");
                return;
            }
            else // save current path and then jump to "home/user" path
            {
                strcpy(buff, SAVED_PATH); // contains saved path
                strcpy(SAVED_PATH, temp); // store the current path
            }
            chdir(buff); //change to previously saved path now in buff.
        }
        else if (AreSame(path, "~") || AreSame(path, ""))
        {
            strcpy(SAVED_PATH, temp); // store the current path
            chdir(USER_HOME_PATH);    // change directory to home path
        }
        else
        {
            printf("%s:\nNo such file or directory :(\n", path);
            return;
        }
    }
    getcwd(buff, MAX_PATH_LEN); // contains current working directory path
    int i = 0, j = 0;

    while (EXECUTABLE_PATH[i] != '\0' && buff[j] != '\0' && EXECUTABLE_PATH[i] == buff[j])
    {
        i++;
        j++;
    }
    if (buff[j] == '\0') // buff ended first implies it is shorter than executable path
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
    strcpy(SAVED_PATH, temp); /* save the previous path.
    current path is in buff and if we need it we can get it using getcwd.
    after this function ends you have SAVED_PATH, CURRENT_DIRECTORY_PATH whose values are retained.
    */
    changed_path = true;
}