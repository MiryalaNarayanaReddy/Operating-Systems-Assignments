#include "redirect_io.h"
#include <fcntl.h>
#include <wait.h>

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

void Redirection(Command command, char *cmnd, char *args)
{
    int sfdi = dup(STDIN_FILENO), sfdo = dup(STDOUT_FILENO);

    bool input = 0;
    bool output = 0;
    bool append = 0;

    char input_file[30];
    char output_file[30];
    char left_over_args[30];

    left_over_args[0] = '\0';
    int stat;
    // tokenize
    char *token;
    char *strptr;

    token = strtok_r(args, " ", &strptr);
    while (token != NULL)
    {
        if (AreSame(token, ">"))
        {
            output = true;
            token = strtok_r(NULL, " ", &strptr);
            strcpy(output_file, token);
        }
        else if (AreSame(token, "<"))
        {
            input = true;
            token = strtok_r(NULL, " ", &strptr);
            strcpy(input_file, token);
        }
        else if (AreSame(token, ">>"))
        {
            append = true;
        }
        if (!(input | output | append))
        {
            if (left_over_args[0] == '\0')
            {
                strcat(left_over_args, token);
            }
            else
            {
                strcat(left_over_args, " ");
                strcat(left_over_args, token);
            }
        }
        token = strtok_r(NULL, " ", &strptr);
    }

    printf("%s\n", left_over_args);
    if (input)
    {
        printf("input = %s\n", input_file);
    }
    if (output)
    {
        printf("output = %s\n", output_file);
    }
    if (append)
    {
        printf("appending\n");
    }

    printf("cmnd = %s\n", cmnd);
    if (!input & output & !append)
    {

        pid_t chd = fork();
        redirect_output(output_file);
        if (chd == 0)
        {
            if (command == __system_process)
            {
                process(cmnd, left_over_args);
            }
            else
            {
                PerformAction(command, left_over_args);
                exit(EXIT_SUCCESS);
            }
        }
        else if (chd < 0)
        {
            perror("internal error: failed to fork ..\n");
        }
        else
        {
            waitpid(chd, &stat, WNOHANG);
        }
    }
    else if (input & !output & !append)
    {

        pid_t chd = fork();
        if (chd == 0)
        {
            redirect_input(input_file);
            if (command == __system_process)
            {
                process(cmnd, left_over_args);
            }
            else
            {
                PerformAction(command, left_over_args);
                exit(EXIT_SUCCESS);
            }
            exit(EXIT_SUCCESS);
        }
        else if (chd < 0)
        {
            perror("internal error: failed to fork ..\n");
        }
        else
        {
            waitpid(chd, &stat, WNOHANG);
        }
    }
    else if (input & output & !append)
    {

        pid_t chd = fork();
        if (chd == 0)
        {
            redirect_input(input_file);
            redirect_output(output_file);
            if (command == __system_process)
            {
                process(cmnd, left_over_args);
            }
            else
            {
                PerformAction(command, left_over_args);
            }
            exit(EXIT_SUCCESS);
        }
        else if (chd < 0)
        {
            perror("internal error: failed to fork ..\n");
        }
        else
        {
            waitpid(chd, &stat, WNOHANG);
        }
    }
    else if (!(input | output | append))
    {

        printf("comming soon..\n");
        pid_t chd = fork();
        if (chd == 0)
        {
            if (command == __system_process)
            {
                process(cmnd, left_over_args);
            }
            else
            {
                PerformAction(command, left_over_args);
                exit(EXIT_SUCCESS);
            }
            exit(EXIT_SUCCESS);
        }
        else if (chd < 0)
        {
            perror("internal error: failed to fork ..\n");
        }
        else
        {
            waitpid(chd, &stat, WNOHANG);
        }
    }
    else
    {
        printf("yet to fiigure\n");
    }
    dup2(sfdi, STDIN_FILENO);
    dup2(sfdo, STDOUT_FILENO);
}