#include "ls.h"

void list_names(char *path, bool include_hidden_files)
{

    DIR *dir = opendir(path);

    struct dirent *curr_dir = readdir(dir);

    while (curr_dir != NULL)
    {
        if ((curr_dir->d_name[0] != '.') || include_hidden_files) // nice way to avoid redundancy of copy paste
        {
            if (curr_dir->d_type == DT_DIR)
            {
                Color_On(__BLUE, BOLD);
                printf("%s\n", curr_dir->d_name);
                Color_Off();
            }
            else
            {
                Bold(true);
                printf("%s\n", curr_dir->d_name);
                Bold(false);
            }
        }
        curr_dir = readdir(dir);
    }
}

void ls(char *args)
{
    char cwd[MAX_PATH_LEN];
    getcwd(cwd, MAX_PATH_LEN);

    if (AreSame(args, ""))
    {
        list_names(cwd, false); // do not list hidden files
    }
    else if (AreSame(args, "-a"))
    {
        list_names(cwd, true); // list all
    }
    else if (AreSame(args, "."))
    {
        list_names(cwd, false);
    }
    else if (AreSame(args, ".."))
    {
        chdir("../");
        char temp[MAX_PATH_LEN];
        getcwd(temp, MAX_PATH_LEN);
        list_names(temp, false);
        chdir(cwd);
    }
    else if (AreSame(args, "~"))
    {
        chdir(USER_HOME_PATH);
        char temp[MAX_PATH_LEN];
        getcwd(temp, MAX_PATH_LEN);
        list_names(temp, false);
        chdir(cwd);
    }
}