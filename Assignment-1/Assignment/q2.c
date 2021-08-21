#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

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
    printf("%d\n", argc);
    int input_fd, output_fd; //file descripters

    char Buffer[BUFFER_SIZE]; //buffer to get some part of input file
    if (argc < 4)             // insufficient arguments
    {
        perror("Invalid argument:\nshould be: ./a.out <input_file_path> <number_of_parts> <index_of_part_to_be_reversed>\n");
        exit(EXIT_FAILURE);
    }

    char input_file_path[MAX_PATH]; //file path
    // adding back slashs if names have spaces in between
    input_file_path[0] = '\0';
    char *temp = " ";
    if (argc > 4) // more than 3 args ==> there are spaces in path
    {
        for (int i = 1; i < argc - 3; i++)
        {
            strcat(input_file_path, argv[i]);
            strcat(input_file_path, temp);
            // print_to_console(input_file_path);
        }
    }

    strcat(input_file_path, argv[argc - 3]); //joining 3rd argument from last
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

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Input file part ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // finding last forward slash and everything after that is file name
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

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Output file part ~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    char output_file_name[MAX_PATH + 13]; // output file
    sprintf(output_file_name, "assignment/2_%s", input_file_name);
    output_fd = open(output_file_name, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
    if (output_fd < 0)
    {
        print_to_console("failed to create file\n");
        exit(EXIT_FAILURE);
    }
    int num_parts = (argv[argc - 2][0] - '0'); //assuming both are single digited numbers
    int part_to_reverse = (argv[argc - 1][0] - '0');

    /////////////////////////////   main part   ////////////////////////////////////

    int sz = lseek(input_fd, 0, SEEK_END); // size of input file
    int part_size = sz / num_parts;
    int part_pos = (part_to_reverse - 1) * part_size;

    //place pointer at the end of part_sized part we need to reverse.
    int pointer = lseek(input_fd, part_pos + part_size, SEEK_SET);

    ssize_t read_size;
    int out_index = 0;

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    while (pointer - BUFFER_SIZE > part_pos) //there is BUFFER sized chunck that can be reversed
    {
        // read buffer from (pointer - BUFFER_SIZE) to (pointer)
        lseek(input_fd, pointer - BUFFER_SIZE, SEEK_SET);
        read_size = read(input_fd, Buffer, BUFFER_SIZE);

        reverse(Buffer, BUFFER_SIZE); //reverse buffer

        //write that buffer from out_index to (out_index + size of buffer)
        lseek(output_fd, out_index, SEEK_SET);
        write(output_fd, Buffer, read_size);
        //show progress
        showprogress((((float)out_index / part_size) * (100)));
        pointer -= BUFFER_SIZE;
        out_index += BUFFER_SIZE;
    }
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    int chunck = pointer - part_pos; // left over chunck
    // read buffer from ( part_pos ) to (part_pos + chunk)
    lseek(input_fd, part_pos, SEEK_SET);
    read_size = read(input_fd, Buffer, chunck);

    reverse(Buffer, chunck); //reverse
    // write to output
    lseek(output_fd, out_index, SEEK_SET);
    write(output_fd, Buffer, read_size);

    out_index += chunck;
    //show progress
    showprogress((((float)out_index / part_size) * (100)));
    print_to_console("\n");
    return 0;
}
