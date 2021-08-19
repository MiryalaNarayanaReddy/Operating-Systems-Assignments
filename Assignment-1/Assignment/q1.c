#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

char progress_bar[101];
#define BUFFER_SIZE 1024
#define MAX_PATH 1024
// 1024 --> 1kB

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

void showprogress(float progress)
{
    fflush(stdout);
    print_to_console("\r");

    char temp[10];
    sprintf(temp, "%5.2f %%", progress);
    print_to_console(temp);
}

void reverse(char *s, int n)
{
    for (int i = 0; i < n / 2; i++)
    {
        char t = s[i];
        s[i] = s[n - 1 - i];
        s[n - 1 - i] = t;
    }
}

int main(int argc, char *argv[])
{
    int input_fd, output_fd; //file descripters

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
    mkdir("assignment", S_IRUSR | S_IWUSR | S_IXUSR);
    output_fd = open("assignment/o.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IXUSR);
    if (output_fd < 0)
    {
        perror("failed to create file\n");
        exit(EXIT_FAILURE);
    }

    int pointer = BUFFER_SIZE;
    size_t read_size;
    int sz = lseek(input_fd, 0, SEEK_END);
    /////////////////////////////
    while (pointer < sz) //for every block
    {
        lseek(input_fd, -pointer, SEEK_END);             // put the pointer pointer bytes before end in inputfile
        read_size = read(input_fd, Buffer, BUFFER_SIZE); // from pointer read 1024 bytes into buffer

        reverse(Buffer, BUFFER_SIZE); //reverse the buffer

        lseek(output_fd, pointer - BUFFER_SIZE, SEEK_SET);
        write(output_fd, Buffer, read_size); //from pointer-buffer_size write buffer into outfile
        pointer += BUFFER_SIZE;
        showprogress((((float)pointer / sz) * (100)));
    }

    ////////////////////////////////
    int leftover_chunck = sz - (pointer - BUFFER_SIZE);
    lseek(input_fd, 0, SEEK_SET);
    read_size = read(input_fd, Buffer, leftover_chunck);

    reverse(Buffer, leftover_chunck);

    lseek(output_fd, pointer - BUFFER_SIZE, SEEK_SET);
    write(output_fd, Buffer, read_size);
    pointer += BUFFER_SIZE;
    showprogress((((float)pointer / sz) * (100)));

    showprogress(100);
    print_to_console("\n");
}
