#include "utils.h"
#include <termios.h>
#include <ctype.h>

#if ENABLED_HISTORY_SCROLL

void die(const char *s)
{
    perror(s);
    exit(1);
}

struct termios orig_termios;

void disableRawMode()
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}

void enableRawMode()
{
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
        die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
}

//gets the whole string upto end of line leaving trailing white spaces.
void get_string(char *s)
{
    char ch;
    setbuf(stdout, NULL);

    enableRawMode();
    memset(s, '\0', MAX_PATH_LEN);
    printf("\r");
    prompt();
    int i = 0;

    while (read(STDIN_FILENO, &ch, 1) == 1)
    {
        if (iscntrl(ch))
        {
            if (ch == '\n')
            {
                printf("\n");
                break;
            }
            else if (ch == 27)
            {
                char buf[3];
                buf[2] = 0;
                if (read(STDIN_FILENO, buf, 2) == 2)
                {
                    printf("\r");
                    prompt();
                    printf("arrowkey : %s", buf);
                }
            }
            else if (ch == 127)
            { // backspace
                if (i > 0)
                {
                    if (s[i - 1] == 9)
                    {
                        for (int k = 0; k < 7; k++)
                        {
                            printf("\b");
                        }
                    }
                    s[--i] = '\0';
                    printf("\b \b");
                }
            }
            else if (ch == 9)
            { // TAB character
                s[i++] = ch;
                for (int k = 0; k < 8; k++)
                { // TABS should be 8 spaces
                    printf(" ");
                }
            }
            else if (ch == 4)
            {
                exit(0);
            }
            else
            {
                printf("%d\n", ch);
            }
        }
        else
        {
            s[i++] = ch;
            printf("%c", ch);
        }
    }
    disableRawMode();
}

#else

//gets the whole string upto end of line leaving trailing white spaces.
void get_string(char *s)
{
    char ch;
    int i = 0;
    while ((ch = getchar()) == ' ') // to remove spaces in the begining
        ;
    if (ch == '\n')
    {
        s[0] = '\n';
        s[1] = '\0';
        return;
    }

    do
    {
        s[i++] = ch;
    } while ((ch = getchar()) != '\n');

    while (s[i - 1] == ' ') //to remove the spaces at the end
    {
        i--;
    }
    s[i] = '\0';
}

#endif

void clean_input()
{
    char ch;
    while ((ch = getchar()) != '\n')
        ;
}

void Bold(bool status)
{
    if (status)
    {

        printf("\e[1m");
    }
    else
    {
        printf("\e[0m");
    }
}

void Color_On(int color, bool bold)
{
    if (bold)
    {
        printf("\033[231;%dm\e[1m", color);
    }
    else
    {
        printf("\033[231;%dm", color);
    }
}

void Color_Off()
{
    printf("\033[m");
}

bool AreSame(char *a, char *b)
{
    if (strcmp(a, b) == 0)
    {
        return true;
    }
    else
        return false;
}
