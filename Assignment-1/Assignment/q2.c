#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

char progress_bar[101];
#define BUFFER_SIZE 16
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
    if (argc < 3)             // insufficient arguments
    {
        perror("Invalid argument:\nshould be: /a.out <input_file_path>\n");
        exit(EXIT_FAILURE);
    }

    char input_file_path[MAX_PATH]; //file path
    // adding back slashs if names have spaces in between
    input_file_path[0] = '\0';
    char *temp = " ";
    if (argc > 3)
    {
        for (int i = 1; i < argc - 3; i++)
        {
            strcat(input_file_path, argv[i]);
            strcat(input_file_path, temp);
            // print_to_console(input_file_path);
        }
    }

    strcat(input_file_path, argv[argc - 3]);
    // print_to_console(input_file_path);
    // print_to_console("\n");
    // print_to_console(argv[argc-2]);
    // print_to_console("\n");
    // print_to_console(argv[argc-1]);

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

    char output_file_name[MAX_PATH + 13]; // output file
    sprintf(output_file_name, "assignment/2_%s", input_file_name);
    output_fd = open(output_file_name, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IXUSR);
    if (output_fd < 0)
    {
        print_to_console("failed to create file\n");
        exit(EXIT_FAILURE);
    }
    int num_parts = atoi(argv[argc - 2]);
    int part_to_reverse = atoi(argv[argc - 1]);

    /////////////////////////////   main part   ////////////////////////////////////

    int sz = lseek(input_fd, 0, SEEK_END); // size of input file
    int part_size = sz / num_parts;
    int part_pos = (part_to_reverse - 1) * part_size;
    /////////////////////////////
    int pointer = lseek(input_fd, 0, SEEK_SET);
    ssize_t read_size;
    while (pointer < part_pos - BUFFER_SIZE)
    {
        lseek(input_fd, pointer, SEEK_SET);
        read_size = read(input_fd, Buffer, BUFFER_SIZE);

        lseek(output_fd, pointer, SEEK_SET);
        write(output_fd, Buffer, read_size);
        showprogress((((float)pointer / sz) * (100)));
        pointer += BUFFER_SIZE;
    }
    // printf("%d %d\n",pointer, part_pos);
    int chunck = part_pos - pointer;

    lseek(input_fd, pointer, SEEK_SET);
    read_size = read(input_fd, Buffer, chunck);

    lseek(output_fd, pointer, SEEK_SET);
    write(output_fd, Buffer, read_size);
    showprogress((((float)pointer / sz) * (100)));

    pointer = part_pos + part_size;
    int o_indx = part_pos;

    /////////////////------
    while (pointer - BUFFER_SIZE > part_pos) //pointer should be greater then the part to be reversed
    {
        lseek(input_fd, pointer, SEEK_SET);
        read_size = read(input_fd, Buffer, BUFFER_SIZE);
        reverse(Buffer, BUFFER_SIZE);
        lseek(output_fd, part_pos, SEEK_SET);
        write(output_fd, Buffer, read_size);

        showprogress((((float)o_indx / sz) * (100)));
        pointer -= BUFFER_SIZE;
        o_indx += BUFFER_SIZE;
    }

    chunck = pointer - part_pos;
    lseek(input_fd, part_pos, SEEK_SET);
    read_size = read(input_fd, Buffer, chunck);
    reverse(Buffer, chunck);

    lseek(output_fd, o_indx, SEEK_SET);
    write(output_fd, Buffer, read_size);
    o_indx += chunck;
    showprogress((((float)o_indx / sz) * (100)));
    //////////////-----------
    pointer = part_pos + part_size;
    while (pointer < sz)
    {
        lseek(input_fd, pointer, SEEK_SET);
        read_size = read(input_fd, Buffer, BUFFER_SIZE);

        lseek(output_fd, pointer, SEEK_SET);
        write(output_fd, Buffer, read_size);
        showprogress((((float)pointer / sz) * (100)));
        pointer += BUFFER_SIZE;
    }
    pointer -= BUFFER_SIZE;
    chunck = sz - pointer;

    lseek(input_fd, pointer, SEEK_SET);
    read_size = read(input_fd, Buffer, chunck);

    lseek(output_fd, pointer, SEEK_SET);
    write(output_fd, Buffer, read_size);
    pointer += chunck;

    showprogress((((float)pointer / sz) * (100)));
    print_to_console("\n");
}
