This contains the following folder structure.

```
Assignment-2
    |
    |
    |___ Shell
    |       |___ main.c
    |       |___ init.c and init.h
    |       |___ user.c and user.h
    |       |___ utils.c and utils.h
    |       |___ signal_handler.c and signal_handler.h
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
    |___ system_commands
    |                  |___ pinfo.c and pinfo.h
    |                  |___ process.c and process.h
    |
    |___ Makefile
    |
    |___ README.md
    |
    |___ .gitignore
    |
    |___ a.out
    |
    |___ LICENSE


```

# Shell

**`main.c`** calls functions from user.c which use functions from all other files.

**`init.c`** has the following functions

- init
- init_cd
- init_process
- init_signal

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

**`signal_handler.c`** has the following functions

- handle_signal
- handle_ctrl_c_signal
- handle_ctrl_z_signal

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

# system_commands

**`pinfo.c`** has the following functions

**`process.c`** has the following functions
