#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

char progress_bar[101];
#define BUFFER_SIZE 128000
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
    sprintf(temp, "%.2f %%", progress);
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
        perror("Invalid argument:\nshould be: /a.out <input_file_path>\n");
        exit(EXIT_FAILURE);
    }

    char input_file_path[MAX_PATH]; //file path
    // adding back slashs if names have spaces in between
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
    // print_to_console(input_file_path);
    // print_to_console("\n");

    input_fd = open(input_file_path, O_RDONLY); // open input file in read mode

    if (input_fd < 0)
    {
        perror("Could not open file\n");
        exit(EXIT_FAILURE);
    }
    mkdir("assignment", S_IRUSR | S_IWUSR | S_IXUSR); // make directory

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

    // print_to_console(input_file_name);
    // print_to_console("\n");

    char output_file_name[MAX_PATH+100]; // output file
    sprintf(output_file_name, "assignment/1_%s", input_file_name);
    output_fd = open(output_file_name, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
    if (output_fd < 0)
    {
        print_to_console("failed to create file\n");
        exit(EXIT_FAILURE);
    }
    /////////////////////////////   main part   ////////////////////////////////////
    int pointer = BUFFER_SIZE;
    size_t read_size;
    int sz = lseek(input_fd, 0, SEEK_END); // size of input file
    /////////////////////////////
    while (pointer < sz) //for every block
    {
        lseek(input_fd, -pointer, SEEK_END);             // put the pointer pointer bytes before end in inputfile
        read_size = read(input_fd, Buffer, BUFFER_SIZE); // from pointer read 1024 bytes into buffer

        reverse(Buffer, BUFFER_SIZE); //reverse the buffer

        lseek(output_fd, pointer - BUFFER_SIZE, SEEK_SET);
        write(output_fd, Buffer, read_size); //from pointer-buffer_size write buffer into outfile
        showprogress((((float)pointer / sz) * (100)));
        pointer += BUFFER_SIZE;
        // sleep(1); //sleep to see the progress for small files
    }

    ////////////////////////////////
    int leftover_chunck = sz - (pointer - BUFFER_SIZE);
    lseek(input_fd, 0, SEEK_SET);
    read_size = read(input_fd, Buffer, leftover_chunck);

    reverse(Buffer, leftover_chunck);

    lseek(output_fd, pointer - BUFFER_SIZE, SEEK_SET);
    write(output_fd, Buffer, read_size);
    pointer += BUFFER_SIZE;

    showprogress(100); //done
    print_to_console("\n");
}
