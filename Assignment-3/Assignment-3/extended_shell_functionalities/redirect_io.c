#include "redirect_io.h"
#include <fcntl.h>
#include <wait.h>
#include <unistd.h>

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

void redirect_output(char *filename, bool append)
{
    int fdi;
    if (append)
    {
        fdi = open(filename, O_RDWR | O_APPEND);
    }
    else
    {
        fdi = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    }

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
    int sfdi = dup(STDIN_FILENO);
    int sfdo = dup(STDOUT_FILENO);
    bool any_redirection = true;
    bool input = 0;
    bool output = 0;
    bool append = 0;

    char input_file[1024];
    char output_file[1024];
    char left_over_args[1024];

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
            token = strtok_r(NULL, " ", &strptr);
            strcpy(output_file, token);
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

    // redirecting stdout and stdin

    if (!input & output & !append) // only >
    {
        redirect_output(output_file, append);
    }
    else if (input & !output & !append) // only <
    {
        redirect_input(input_file);
    }
    else if (input & output & !append) // both > and <
    {
        redirect_input(input_file);
        redirect_output(output_file, append);
    }
    else if (!input & !output & append) // only >>
    {
        redirect_output(output_file, append);
    }
    else if (input & !output & append) // both < and >>
    {
        redirect_output(output_file, append);
    }
    else
    {
        // nothing
        // printf("yet to figure\n");

        //invalid cases
        // both > and >>
        // all < > >>
        any_redirection = false;
    }

    if (command == __system_process)
    {
        process(cmnd, left_over_args);
    }
    else
    {
        PerformAction(command, left_over_args);
        // printf("redirection\n");
    }

    if (any_redirection)
    {
        dup2(sfdi, STDIN_FILENO);
        dup2(sfdo, STDOUT_FILENO);
    }
    close(sfdi);
    close(sfdo);
    // printf("done\n");
}