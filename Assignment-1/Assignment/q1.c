#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

char progress_bar[101];
#define BUFFER_SIZE 10
#define MAX_PATH 1024
// 1024 1kB

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

//100.00 % [####################################################################################################]

void showprogress(float progress)
{
    fflush(stdout);
    print_to_console("\r");
    for (int i = 0; i < progress; i++)
    {
        progress_bar[i] = '#';
    }
    char temp[115];

    sprintf(temp, "%5.2f %% [%-100s]", progress, progress_bar);
    print_to_console(temp);
}

void reverse(char *s)
{
    for (int i = 0; i < BUFFER_SIZE / 2; i++)
    {
        char t = s[i];
        s[i] = s[BUFFER_SIZE - 1 - i];
        s[BUFFER_SIZE - 1 - i] = t;
    }
}

int main(int argc, char *argv[])
{
    int input_fd, output_fd; //file discrepters

    char Buffer[BUFFER_SIZE]; //buffer to get some part of input file
    if (argc < 2)             // insufficient arguments
    {
        perror("Invalid argument:\n.should be: /a.out <input_file_path>");
        exit(EXIT_FAILURE);
    }
    char input_file_path[MAX_PATH]; //file path
    // adding back slashs if names have spaces in between
    input_file_path[0] = '\0';
    char *temp = "\\ ";
    if (argc > 2)
    {
        for (int i = 1; i < argc - 1; i++)
        {
            strcat(input_file_path, argv[i]);
            strcat(input_file_path, temp);
            print_to_console(input_file_path);
        }
    }

    strcat(input_file_path, argv[argc - 1]);
    print_to_console(input_file_path);
    print_to_console("\n");
    input_fd = open(input_file_path, O_RDONLY);
    if (input_fd < 0)
    {
        perror("Could not open file\n");
        exit(EXIT_FAILURE);
    }
    output_fd = open("o.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IXUSR);
    if (output_fd < 0)
    {
        perror("failed to create file\n");
        exit(EXIT_FAILURE);
    }

    int pointer = BUFFER_SIZE;
    size_t read_size;
    int sz = lseek(input_fd, 0, SEEK_END);
    /////////////////////////////
    while (pointer < sz)
    {
        lseek(input_fd, -pointer, SEEK_END);
        read_size = read(input_fd, Buffer, BUFFER_SIZE);

        reverse(Buffer);

        lseek(output_fd, pointer - BUFFER_SIZE, SEEK_SET);
        write(output_fd, Buffer, read_size);
        pointer += BUFFER_SIZE;
        showprogress((float)pointer / sz);
    }
    ////////////////////////////////

 
    showprogress(100);
    print_to_console("\n");
}
