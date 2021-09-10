This contains the following folder structure.

```
Assignment-2
    |
    |
    |___ Shell
    |       |___ main.c
    |       |___ user.c and user.h
    |       |___ utils.c and utils.h
    |
    |
    |___ cd
    |     |___cd.c and cd.h
    |     |___
    |
    |
    |___ ls
    |     |___ls.c and ls.h
    |     |___
    |
    |
    |___Make file
    |
    |
    |___ Readme.md
    |

```

# Shell

**`main.c`** calls functions from user.c which use functions from all other files.


**`user.c`** has following functions
- prompt
- Get_Command
- process_command
- encode_command
- PerformAction

**`utils.c`** has the following functions

- Bold
- Color_On
- Color_Off
- clean_input
- get_string
- AreSame ( char *a, char *b );

