#include "redirect_io.h"
#include <fcntl.h>

void init_redirection()
{
    stdin_fd_saved = dup(STDIN_FILENO);
    stdout_fd_saved = dup(STDOUT_FILENO);
}

void disable_redirection()
{
    dup2(stdin_fd_saved, STDIN_FILENO);
    dup2(stdout_fd_saved, STDOUT_FILENO);
}

void redirect_input(char *filename)
{
    int fdi = open(filename, O_RDONLY);
    if (fdi < 0)
    {
        printf("%s doesnot exist\n", filename);
        return;
    }
    if (dup2(fdi, STDIN_FILENO) < 0)
    {
        perror("could not duplicate file descriptor\n");
        return;
    }
    close(fdi);
}

void redirect_output(char *filename)
{
    int fdi = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fdi < 0)
    {
        printf("%s doesnot exist\n", filename);
        return;
    }
    if (dup2(fdi, STDOUT_FILENO) < 0)
    {
        perror("could not duplicate file descriptor\n");
        return;
    }
    close(fdi);
}

