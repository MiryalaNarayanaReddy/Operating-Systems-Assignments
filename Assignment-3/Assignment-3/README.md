This contains the following folder structure.

```
Assignment-3
    |
    |________ Shell
    |          |___ main.c
    |          |___ init.c and init.h
    |          |___ user.c and user.h
    |          |___ utils.c and utils.h
    |          |___ signal_handler.c and signal_handler.h
    |
    |________ builtin_commands
    |          |___cd.c and cd.h
    |          |___echo.c and echo.h
    |          |___pwd.c and pwd.h
    |
    |_________ls
    |          |___ls.c and ls.h
    |
    |________ system_commands
    |          |___ pinfo.c and pinfo.h
    |          |___ process.c and process.h
    |          |___ repeat.c and repeat.h
    |
    |________ history
    |          |___ history.c and history.h
    |          |___ history.txt
    |
    |
    |________ extended_shell_functionalities
    |          |___ redirect_io.c and redirect_io.h
    |          |___ pipe.c and pipe.h
    |          |___ jobs.c and jobs.h
    |
    |
    |________ Makefile
    |
    |________ README.md
    |
    |________ .gitignore
    |
    |________ a.out
    |
    |________ LICENSE


```

# Shell

**`main.c`** 

- init() to initialize global variables 
- functions from user.c which use functions from all other files.

**`init.c`** has the following functions

|**function**|**purpose**|
|--------|-------|
| *init* | calls all init functions | 
| *init_cd* | initializes some global paths |
| *init_process* | initiallizes some global variables for proccess.c |
| *init_signal*|  initializes signals|
| *init_history* | initializes the history file path from user home path|

**`user.c`** has following functions

|**function**|**purpose**|
|--------|-------|
| *prompt* | prints the prompt |
| *Get_Command* | gets the command using get_string function|
| *tokenize* | removes extra spaces between words |
| *process_command* | gets the command word and uses both encode_command and PerformAction functions |
| *encode_command* | encodes command to respective integer equivalent|
| *PerformAction* | uses switch and it calls rspective command functions  |


**`utils.c`** has the following functions

|**function**|**purpose**|
|--------|-------|
| *Color_On* | enables color and Boldness of stdout based on arguments  |
| *Color_Off* | disables any color or boldness |
| *Bold* |  make consequent stdout Bold or not bold based on the arguments | 
| *clean_input* | cleans the input upto newline |
| *get_string* | scans the string upto newline excluding spaces in starting and ending |
| *AreSame* | checks if two strings are same |


**`signal_handler.c`** has the following functions

|**function**|**purpose**|
|--------|-------|
| *handle_signal* | handles signals uses following two functions |
| *handle_ctrl_c_signal* | handles ctrl-c signal |
| *handle_ctrl_z_signal* | handles ctrl-z signal |

# builtin_commands

**`echo.c`** has the following functions
|**function**|**purpose**|
|--------|-------|
| *echo* | prints the args passed as input |


**`cd.c`** has the following functions

|**function**|**purpose**|
|--------|-------|
| *cd* | changes pwd based on arguments passed |


**`pwd.c`** has the following functions

|**function**|**purpose**|
|--------|-------|
| *pwd* | prints the present working directory path from home |


# ls

**`ls.c`** has the following functions

|**function**|**purpose**|
|--------|------- |
| *ls* | tokonizes args, flags and calls process_ls |
| *process_ls* | calls list_names based on flags |
| *list_names* | for each file(or dir) in directory , print names accordingly |
| *print_name* | prints details(if flags demand) and names of directories or files passed |
| *list_details* | prints long format for ls |
| *number_of_disk_blocks* | returs number of 512 byte blocks occupied by path|
| *month_name* | converts int [ 0..11 ] to corresponding month |


# system_commands

**`pinfo.c`** has the following functions

|**function**|**purpose**|
|--------|------- |
| *pinfo* | takes the pid and prints the process info |


**`process.c`** has the following functions

|**function**|**purpose**|
|--------|------- |
| *process* | uses parse_cmd, forground_process and background_process |
| *parse_cmd* | tokenizes commands with " " as delimiter |
| *forground_process* | runs forground process |
| *background_process* | runs background process |
| *process_status* | checks for background process status |


**`repeat.c`** has the following functions

|**function**|**purpose**|
|--------|------- |
| *repeat* |repeats the command n number of times using process_command |
| *string_to_int* |converts a string to integer. if not possible returns -1|


# history

**`history.c`** has the following functions

|**function**|**purpose**|
|--------|------- |
| *history* | prints all or n lines of history|

# extended_shell_functonalities

**`redirect_io.c`** has the following functions

|**function**|**purpose**|
|------------|----------- |
| *redirect_input* | points stdin to a file |
| *redirect_output* | points stdout to a file |


**`pipe.c`** has the following functions

|**function**|**purpose**|
|--------|------- |

**`jobs.c`** has the following functions

|**function**|**purpose**|
|--------|------- |


## other files

`README .md`

`LICENSE`

`Makefile`

run the following commands:

```
user@systemname:~$ make clean
user@systemname:~$ make 
user@systemname:~$ make clean
user@systemname:~$ ./a.out
```