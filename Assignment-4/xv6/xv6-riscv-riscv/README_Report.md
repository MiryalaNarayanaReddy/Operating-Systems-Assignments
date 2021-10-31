# **Report**

# ***specification 1***

## syscall **trace**

|Function|Addition/ modification|
|------|------|
| kernel/syscall.c - **syscall()** | In loop check if the trace_mask of the currently running process has the ith bit set and print process pid, syscall name and arguments passed to it.After executing the syscall print the return value.   |
|kernel/syscall.c - **name_of_syscall()**| function that prints the name and arguments of a syscall using switch case|
|kernel/sysproc.c - **sys_trace()**|gets the first argument of trace system call using argaddr() function and passes it to trace()|
|kernel/proc.c - **trace()**| set my_proc()->trace to passed trace value |

- other minor additions and modifications
    - modifying **fork()** to copy trace to its child
    - adding syscall trace in two parts of **syscall.c** and once in **syscall.h**
    - adding trace syscall in **defs.h**

## user command **strace**

- additions and modifications
    - adding $U/_strace to UPROGS in **Makefile**
    - adding a new program **strace.c** to user/
        - we take the arguments and parse them and get mask and commad to execute..
        - call trace(mask)
        - fork and  exec (command) will have same mask.
    - adding **trace** in user/usys.pl file
    - adding **trace** in user/user.h file


# ***specification 2***

- Added lines in **Makefile** to select the SCHEDULER by passing arguments to **make qemu**

 - add the waitx syscall done in tutorial 

##  **FCFS**
- Additions and modifications 
    - kernel/proc.c - scheduler()
        - using a for loop to go thorugh all process and selecting one with lowest **ctime** and scheduling it to run.
    - kernel/trap.c - usertrap() & kerneltrap()
        - disabled preemption() due to timer interrupt by removing yield() option during FCFS

##  **PBS**
- Additions and modifications 
    -kernel/proc.h -  added fields priority, niceness, running_time, sleeping_time to struc proc

|Function|Addition/ modification|
|------|------|
|kernel/proc.c - **allocproc()** | default priority is set to 60 , niceness to 5 running_time,sleeping_time  to 0 during creating process in allocproc() |
|kernel/proc.c - **Compute_niceness()** |calculates niceness using sleeping time and running time and returns it|
|kernel/proc.c - **Dynamic_priority()** |uses static priority and niceness to calculate the Dynamic priority |
|kernel/proc.c - **set_priority()** | A system call added to set the priority of a process with given pid|
|user/**setpriority.c**   | user command to use the system call set_priority|
|kernel/proc.c - **preemption_possible()**|Checks if there is any process that has higher priority than current process and yield() is there is one. This is called by usertrap and kernel trap functions in kernel/trap.c when timer interrupt occurs|
|kernel/proc.c - **update_time()**|added a line to update running_time as well|
|kernel/proc.c - **sleep()**|set sleeping_time to ticks and |
|kernel/proc.c - **wakeup()**| set sleeping time to ticks - sleeping_time to get the overall sleeping time |

- for calculating sleeping_time we could 
    - set sleeping_time to 0 in sleep()
    - add code to  update_time() function to increament sleeping time of those processes that are sleeping.
    - The only issue here was how to stop updating when wakeup is called ? Hence I used the above the approach insteading of complicating sleeping_time for myself.
- for syscall set_priority and user command setpriority similar approach as mentioned in specification 1 is used.

##  **MLFQ**
- Additions and modifications 
    - added following fields to struct proc in proc.h
        - **priority_queue_number**  queue number in which process process is present 
        - **priority queue[5]**   time process spent in differet queues
        - **enque_time**   process enque time
    - in allocproc set all the above to zero and enque_time to ticks

|Function|Addition/ modification|
|------|------|
|kernel/proc.c - **scheduler()** | update the priority_queue_number if crossed aging limit. Then select process from each queue. Finaly select the best one from all five selected ones when higher priority ones do not exist |
|kernel/proc.c - **crossed_time_slice()** | checks if the process running_time has crossed its time slice and increament its queue number . This is used by usertrap() and kerneltrap() functions in kernel/trap.c when timer interrupt occurs |

# ***specification 3***

- based on the scheduler defined in the procdump() printing line is selected using preprocessor directives #ifdef and #endif.
    - for PBS
        - priority shows the priority value of the process.
    - for MLFQ 
        - priorty is priority_queue_number of the process
        - q0 to q4 are printed showing time spent in each


