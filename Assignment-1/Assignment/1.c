#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#define BUFFER_SIZE 10

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
    int input_fd, output_fd;
    int open_flags, file_permissions;
    char Buffer[BUFFER_SIZE];
    if (argc < 2)
    {
        perror("Invalid argument:\n.should be: /a.out <input_file_path>");
        exit(EXIT_FAILURE);
    }
    input_fd = open(argv[1], O_RDONLY);
    if (input_fd < 0)
    {
        perror("Could not open file\n");
        exit(EXIT_FAILURE);
    }
    open_flags = O_CREAT | O_WRONLY | O_TRUNC;
    file_permissions = S_IRUSR | S_IWUSR | S_IXUSR;
    output_fd = open(argv[2], open_flags, file_permissions);
    if (output_fd < 0)
    {
        perror("failed to create file\n");
        exit(EXIT_FAILURE);
    }
    ssize_t num_read;
    // while ((num_read = read(input_fd, Buffer, BUFFER_SIZE)) > 0)
    // {
    //     if(write(output_fd,Buffer,num_read)!=num_read){
    //         perror("could not write buffer\n");
    //     }
    // }

    lseek(input_fd, -10, SEEK_END);
    num_read = read(input_fd, Buffer, BUFFER_SIZE);
    reverse(Buffer);
    if (write(output_fd, Buffer, num_read) != num_read)
    {
        perror("could not write buffer\n");
    }
    lseek(input_fd, -20, SEEK_END);

    num_read = read(input_fd, Buffer, BUFFER_SIZE);
    reverse(Buffer);
    if (write(output_fd, Buffer, num_read) != num_read)
    {
        perror("could not write buffer\n");
    }
}
