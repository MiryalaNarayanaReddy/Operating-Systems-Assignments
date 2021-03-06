#include "ls.h"
#include <sys/stat.h>
#include <pwd.h> // getpwuid
#include <grp.h> // getgrgid
#include <time.h>
#include <string.h>

void ls(char *args)
{
    char cwd[MAX_PATH_LEN];
    getcwd(cwd, MAX_PATH_LEN);

    char dir_paths[10][MAX_PATH_LEN];
    int count = 0;
    bool l = false, a = false;

    // tokenize

    char *token;
    char *strptr;

    token = strtok_r(args, " ", &strptr);

    while (token != NULL)
    {
        if (AreSame(token, "-l"))
        {
            l = true;
        }
        else if (AreSame(token, "-al") || AreSame(token, "-la"))
        {
            l = a = true;
        }
        else if (AreSame(token, "-a"))
        {
            a = true;
        }
        else
        {
            strcpy(dir_paths[count], token);
            count++;
        }

        token = strtok_r(NULL, " ", &strptr);
    }
    // get flags
    char flags[4];
    if (l & a)
    {
        strcpy(flags, "-al");
    }
    else if (l)
    {
        strcpy(flags, "-l");
    }
    else if (a)
    {
        strcpy(flags, "-a");
    }
    else
    {
        strcpy(flags, "");
    }

    // for each directory
    if (count == 0)
    {
        if (AreSame(flags, "-al") || AreSame(flags, "-l"))
        {
            int total_blocks = number_of_disk_blocks(cwd);
            if (total_blocks != -1)
            {
                Bold(true);
                printf("total %d\n", total_blocks);
                Bold(false);
            }
        }
        process_ls(cwd, flags); // call for processing
    }
    else
    {
        char ls_wd[MAX_PATH_LEN]; //ls working directory
        for (int i = 0; i < count; i++)
        {
            // printf("%s\n",dir_paths[i]);
            bool failed = chdir(dir_paths[i]); //returns 1 if fails.
            if (!failed)
            {

                // we changed into that directory now do ls as if we in that directory (of course we are in it)
                Color_On(__PINK, BOLD);
                printf("%s:\n", dir_paths[i]); // print directory name
                Color_Off();
                getcwd(ls_wd, MAX_PATH_LEN); // get working directory path after changing directory

                int total_blocks = number_of_disk_blocks(ls_wd);
                if (total_blocks != -1)
                {
                    Bold(true);
                    printf("total %d\n", total_blocks);
                    Bold(false);
                }
                else
                {
                    continue; // :(  nothing to do go on with the others
                }

                process_ls(ls_wd, flags); // call for processing

                chdir(cwd); // change back to original directory.
                printf("\n");
            }
            else
            {
                if (AreSame(dir_paths[i], "~"))
                {
                    chdir(USER_HOME_PATH);
                    Color_On(__PINK, BOLD);
                    printf("%s:\n", USER_HOME_PATH);
                    Color_Off();
                    process_ls(USER_HOME_PATH, flags); // call for processing
                    chdir(cwd);                        // change back to original directory.
                    printf("\n");
                }
                else
                {
                    Color_On(__RED, BOLD);
                    printf("%s\n: No such directory\n", dir_paths[i]);
                    Color_Off();
                }
            }
        }
    }
}

void process_ls(char *cwd, char *flags)
{
    if (AreSame(flags, ""))
    {
        list_names(cwd, false, false); // do not list hidden files
    }
    else if (AreSame(flags, "-a"))
    {
        list_names(cwd, true, false); // list all
    }
    else if (AreSame(flags, "-l"))
    {
        list_names(cwd, false, true);
    }
    else if (AreSame(flags, "-al"))
    {
        list_names(cwd, true, true);
    }
    else
    {
        Color_On(__RED, BOLD);
        printf("%s\n No such directory", cwd);
        Color_Off();
        // never happens as far as I see ... but just added it for completeness and neatness :)
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
                print_name(curr_dir->d_name, details, true);
            }
            else
            {
                print_name(curr_dir->d_name, details, false);
            }
        }
        curr_dir = readdir(dir);
    }
    closedir(dir); // good to close eventhough function ends without any problem.
}

void print_name(char *name, bool details, bool isdir)
{
    if (details)
    {
        list_details(name); // list details i.r., in long format
    }

    // print name in color depending on its type (directory or file)
    if (isdir)
    {
        Color_On(__BLUE, BOLD);
        printf("%s\n", name);
        Color_Off();
    }
    else
    {
        // Bold(true);
        printf("%s\n", name);
        // Bold(false);
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
    printf("%5d ", (unsigned int)file_stats.st_nlink);

    struct passwd *pw = getpwuid(file_stats.st_uid);
    struct group *gr = getgrgid(file_stats.st_gid);
    printf("%s %s ", pw->pw_name, gr->gr_name);

    printf("%10ld ", file_stats.st_size);

    struct timespec last_modify_time = file_stats.st_mtim;
    struct tm *lmdate = localtime(&(last_modify_time.tv_sec));
    printf("%s %2d ", month_name(lmdate->tm_mon), lmdate->tm_mday); // month , date

    int year, month, hour, minute; // stroing the lmdate values
    year = lmdate->tm_year;
    month = lmdate->tm_mon;
    hour = lmdate->tm_hour;
    minute = lmdate->tm_min;

    struct tm *today;
    time_t t;
    t = time(NULL);
    today = localtime(&t);

    if (today->tm_year > year || today->tm_mon - 6 >= month)
    {
        printf("%5d ", 1900 + year); // year
    }
    else
    {
        printf("%2d:%2d ", hour, minute); // hour , minutes
    }
}

int number_of_disk_blocks(char *path)
{
    struct dirent *curr_dir;
    struct stat file_stats;
    int total = 0;
    char temp[MAX_PATH_LEN];
    strcpy(temp, path);
    int len = strlen(path);
    DIR *dir = opendir(path);
    curr_dir = readdir(dir);
    while (curr_dir != NULL)
    {
        if (curr_dir->d_name[0] != '.')
        {
            temp[len] = '\0';
            strcat(temp, "/");
            strcat(temp, curr_dir->d_name); // path to the current file or folder.

            if (stat(temp, &file_stats) >= 0)
            {
                total += file_stats.st_blocks / 2;
            }
            else
            {
                printf("counting number of blocks for \"%s\" error", curr_dir->d_name);
                return -1;
            }
        }
        curr_dir = readdir(dir);
    }
    return total;
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
