#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>

#define MAX_PATH 1024

size_t length_of_string(char *s)
{
    size_t len = 0;
    while (s[len] != '\0')
    {
        len++;
    }
    return len;
}

void print_to_console(char *s)
{
    write(1, s, length_of_string(s));
}

void print_permission(char *who, char *what, char *filename, bool perm)
{
    char s[MAX_PATH];
    sprintf(s, "%s has %s permission on %s: %s\n", who, what, filename, perm ? "Yes" : "No");
    print_to_console(s);
}

void permissions(char *file_name, char *name_to_print)
{
    struct stat file_stats;

    if ((stat(file_name, &file_stats)) == -1)
    {
        perror("file error\n");
        exit(EXIT_FAILURE);
    }

    print_permission("User", "read", name_to_print, file_stats.st_mode & S_IRUSR);
    print_permission("User", "write", name_to_print, file_stats.st_mode & S_IWUSR);
    print_permission("User", "execute", name_to_print, file_stats.st_mode & S_IXUSR);

    print_to_console("\n");

    print_permission("Group", "read", name_to_print, file_stats.st_mode & S_IRGRP);
    print_permission("Group", "write", name_to_print, file_stats.st_mode & S_IWGRP);
    print_permission("Group", "execute", name_to_print, file_stats.st_mode & S_IXGRP);

    print_to_console("\n");

    print_permission("Others", "read", name_to_print, file_stats.st_mode & S_IROTH);
    print_permission("Others", "write", name_to_print, file_stats.st_mode & S_IWOTH);
    print_permission("Others", "execute", name_to_print, file_stats.st_mode & S_IXOTH);

    print_to_console("\n");

    // printf("bits = %x\n", file_stats.st_mode);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        perror("Invalid argument:\nshould be: /a.out <input_file_path>\n");
        exit(EXIT_FAILURE);
    }

    char input_file_path[MAX_PATH]; //file path
    input_file_path[0] = '\0';
    char *temp = " ";
    if (argc > 2)
    {
        for (int i = 1; i < argc - 1; i++)
        {
            strcat(input_file_path, argv[i]);
            strcat(input_file_path, temp);
            // print_to_console(input_file_path);
        }
    }

    strcat(input_file_path, argv[argc - 1]);

    // finding last forward slash
    int i = -1, j = 0;
    while (input_file_path[j] != '\0')
    {
        if (input_file_path[j] == '/')
        {
            i = j + 1;
        }
        j++;
    }
    if (i == -1) // no forward slash
    {
        i = 0;
    }
    char input_file_name[MAX_PATH]; // to store input file name
    int k = i;
    for (; k <= j; k++)
    {
        input_file_name[k - i] = input_file_path[k];
    }
    input_file_name[k] = '\0';

    struct stat dir_stat;

    if ((stat("Assignment", &dir_stat)) == -1)
    {
        perror("directory error\n");
        exit(EXIT_FAILURE);
    }
    if ((dir_stat.st_mode & S_IFMT) == S_IFDIR)
    {
        print_to_console("Directory is created: Yes\n\n");
    }
    else
    {
        print_to_console("Directory is created: No\n\n");
    }

    char temp2[MAX_PATH + 100];

    sprintf(temp2, "Assignment/1_%s", input_file_name);
    permissions(temp2, "output_file_1");
    print_to_console("\n");

    sprintf(temp2, "Assignment/2_%s", input_file_name);
    permissions(temp2, "output_file_2");
    print_to_console("\n");

    permissions("Assignment", "directory");
    print_to_console("\n");
}
