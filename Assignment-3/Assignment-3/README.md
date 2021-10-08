
`Note:` In this whole file, the function names are only specified, while writing them in the flow chart and describing  them briefly in the tables. The arguments' are not specified anywhere in this file. If needed one can refer to respective `.h` or  .c file which contains it.

# ***compilation commands***
run the following commands in the folder containing **makefile** to start this shell program

```
user@systemname:~$ make clean
user@systemname:~$ make 
user@systemname:~$ make clean
user@systemname:~$ ./a.out
```
# ***flow chart of my program execution***
```
main.c
     |
    \|/
    init()
     |   - init_cd()
     |   - init_process()
     |       - handle_signal() 
     |           -  handle_ctrl_c_signal();
     |           -  handle_ctrl_z_signal();
     |       - Handel_background_process_exit()
     |           - get_id_of_bg_process()
     |   - init_signal()
     |   - init_history()
     |
  _\_|
 | / |
 |  \|/
 | prompt()
 |   |
 |  \|/
 | Get_Command() - get_string()
 |   |           - push_into_history()
 |   |
 |  \|/
 | check_for_pipes() - strip_spaces() 
 |   |               - pipe_all() 
 |   |                  - process_command()
/|\  |               -  process_command() 
 |___|                     |
                          \|/
                        - tokenize()
                        - encode_command()
                        - Redirection()
                                |
                               \|/
                            - redirect_output()
                            - redirect_input()
                            - process() { for system commands}
                                        |
                                       \|/
                                        - calls respective functions 
                                            - forground_process()
                                                - push_into_jobs()
                                            - background_process()
                                                - push_into_jobs()
                                            - parse_cmd()
                            - PerformAction() { for built_in_commands written by me }
                                        |
                                       \|/
                                        - calls respective functions 
                                            - cd()
                                            - ls()
                                                |
                                               \|/
                                                - number_of_disk_blocks()
                                                - process_ls()
                                                    - list_names()
                                                        - print_name()
                                                            - list_details()
                                                                - month_name()
                                            - echo()
                                            - pwd()
                                            - pinfo()
                                            - repeat()
                                                - string_to_int()
                                                - process_command()
                                            - history()
                                            - list_jobs()
                                                - pstatus()
                                                - expand_status()
                                            - kill_job()
                                                - string_to_int()
                                            - fg()
                                                - string_to_int()
                                            - bg()
                                                 - string_to_int()
                                            - replay()
                                                 - string_to_int()
                                                 - process_command()
```

# ***folder structure***

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
    |          |___ replay.c and replay.h
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
|*Handel_background_process_exit*|detects SIGCHLD signal and calls handler "background_process_exit_message" |
|*background_process_exit_message*| prints the child exit message having name of process, id and exit status . Uses "get_id_of_bg_process" to get id of the process.|
|*get_id_of_bg_process*|returns process id or number in jobs' list for corresponding pid |


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
| *redirect_input* | takes in a file path and points stdin to a file using dup2 function |
| *redirect_output* |  takes in a file path and points stdout to a file using dup2 function |
| *void Redirection* | checks for neccessary redirections and use above functions to make those redirections. This function is called by process_command function which intern is called by check_for_pipes function invoked by main.c |

**`pipe.c`** has the following functions

|**function**|**purpose**|
|--------|------- |
| *check_for_pipes* | This is called by main.c .This checks for pipes and pipes them all using pipe_all and if there are no pipes then it calls process_command function directly.
| *pipe_all* | pipes all command and executes each using process_command function |
| *strip_spaces* | removes extra spaces at both ends of a string . This is used by check_for_pipes functon before piping all commands |

**`jobs.c`** has the following functions

|**function**|**purpose**|
|--------|------- |
| *push_into_jobs* | pushes a background process command into the jobs list|
| *list_jobs* |prints all background process ( stopped or running ) and their status' using both pstatus and expand_status functions |
| *pstatus* |returns the status of a background process reading /proc/pid/stat file ( Here if the status is S then it returns R implying that it is running in background but when the current processs is running the background proces was sleeping. ) The same thing happens with **ps** command unlike **jobs** command in linux terminal|
| *expand_status* |Just gives the full status name like 'Running' for 'R' etc.,|
| *kill_job*|This funcion is called when **sig** command is used. This sends a given signal to a process with given pid  |
| *fg* | Brings a background running process to forground. This sets the forground process id to pid of background process and calls wait on this.after wait it rests the grop id to main process. |
| *bg* | changes the state of stopped process in background to running in background by sending a SIGCONT signal to it. |

**`replay.c`** has the following functions

|**function**|**purpose**|
|--------|------- |
| *replay* | repeats a command every i seconds upto p seconds where i is interval and p is period according to command specifations.This function calls string_to_int and process_command functions. |

## other files

`README.md`

`LICENSE`

`Makefile`
