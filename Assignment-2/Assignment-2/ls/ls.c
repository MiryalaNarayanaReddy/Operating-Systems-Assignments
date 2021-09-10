#include "ls.h"
#include <sys/stat.h>
#include <pwd.h> // getpwuid
#include <grp.h> // getgrgid
#include <time.h>

void print_name(char *name, bool details)
{
    if (!details)
    {
        printf("%s\n", name);
    }
    else
    {
        list_details(name);
        printf("\n");
    }
}

void list_names(char *path, bool include_hidden_files, bool details)
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
                print_name(curr_dir->d_name, details);
                Color_Off();
            }
            else
            {
                Bold(true);
                print_name(curr_dir->d_name, details);
                Bold(false);
            }
        }
        curr_dir = readdir(dir);
    }
}

void list_details(char *name)
{
    struct stat file_stats;
    if (stat(name, &file_stats) < 0)
    {
        Color_On(__YELLOW, !BOLD);
        printf("could not access details of %s\n", name);
        Color_Off();
    }
    printf((file_stats.st_mode & S_IFDIR) ? "d" : "-");
    printf((file_stats.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stats.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stats.st_mode & S_IXUSR) ? "x" : "-");
    printf((file_stats.st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stats.st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stats.st_mode & S_IXGRP) ? "x" : "-");
    printf((file_stats.st_mode & S_IROTH) ? "r" : "-");
    printf((file_stats.st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stats.st_mode & S_IXOTH) ? "x" : "-");
    printf(" ");
    printf("%2d ", (unsigned int)file_stats.st_nlink);

    struct passwd *pw = getpwuid(file_stats.st_uid);
    struct group *gr = getgrgid(file_stats.st_gid);
    printf("%s %s ", pw->pw_name, gr->gr_name);

    printf("%8ld ", file_stats.st_size);
    struct timespec last_modify_time = file_stats.st_mtim;
    struct tm *lmdate = localtime(&(last_modify_time.tv_sec));
    printf("%s %2d %2d:%2d ", month_name(lmdate->tm_mon), lmdate->tm_mday, lmdate->tm_hour, lmdate->tm_min);

    printf("%s ", name);
}

void ls(char *args)
{
    char cwd[MAX_PATH_LEN];
    getcwd(cwd, MAX_PATH_LEN);

    if (AreSame(args, ""))
    {
        list_names(cwd, false, false); // do not list hidden files
    }
    else if (AreSame(args, "-a"))
    {
        list_names(cwd, true, false); // list all
    }
    else if (AreSame(args, "."))
    {
        list_names(cwd, false, false);
    }
    else if (AreSame(args, ".."))
    {
        chdir("../");
        char temp[MAX_PATH_LEN];
        getcwd(temp, MAX_PATH_LEN);
        list_names(temp, false, false);
        chdir(cwd);
    }
    else if (AreSame(args, "~"))
    {
        chdir(USER_HOME_PATH);
        char temp[MAX_PATH_LEN];
        getcwd(temp, MAX_PATH_LEN);
        list_names(temp, false, false);
        chdir(cwd);
    }
    else if (AreSame(args, "-l"))
    {
        list_names(cwd, false, true);
    }
    else if (AreSame(args, "-al"))
    {
        list_names(cwd, true, true);
    }
    else
    {
    }
}

char *month_name(int month)
{
    switch (month)
    {
    case 0:
        return "Jan";
        break;
    case 1:
        return "Feb";
        break;
    case 2:
        return "Mar";
        break;
    case 3:
        return "Apr";
        break;
    case 4:
        return "May";
        break;
    case 5:
        return "Jun";
        break;
    case 6:
        return "Jul";
        break;
    case 7:
        return "Aug";
        break;
    case 8:
        return "Sep";
        break;
    case 9:
        return "Oct";
        break;
    case 10:
        return "Nov";
        break;
    case 11:
        return "Dec";
        break;
    }
}