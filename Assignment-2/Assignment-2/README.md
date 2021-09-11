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
    |___ builtin_commands
    |                  |___cd.c and cd.h
    |                  |___echo.c and echo.h
    |                  |___pwd.c and pwd.h
    |
    |___ ls
    |     |___ls.c and ls.h
    |
    |
    |___Make file
    |
    |___ Readme.md
    |
    |__ .gitignore
    |
    |___ LICENSE


```

# Shell

**`main.c`** calls functions from user.c which use functions from all other files.


**`user.c`** has following functions
- prompt
- Get_Command
- tokenize
- process_command
- encode_command
- PerformAction

**`utils.c`** has the following functions

- Color_On
- Color_Off
- clean_input
- get_string
- AreSame


# builtin_commands

**`echo.c`** has the following functions
- echo

**`cd.c`** has the following functions
- cd

**`pwd.c`** has the following functions
- pwd

# ls

**`ls.c`** has the following functions

- ls
- process_ls
- list_names
- print_name
- list_details
- month_name
