# An alternate course allocation Portal

folder structure

```
   q1
    |
    |______ main.c 
    |
    |______ user.c & user.h 
    |
    |______ group.c & group.h
    |
    |______ person.c & person.h
    |
    |______ zone.c & zone.h
    |
    |______ goal.c & goal.h
    |
    |______ stimer.c & stimer.h
    |
    |______ Makefile
    |
    |______ i.txt

```

## **main.c** 
- declares global variables and intializes mutex locks
- calls init_all_threads()


## **user.c**
- **``init_all_threads()``**
    - takes input and fills the datastructues that store respective data
    - create **group_list [ ]**, a list of **struct group**
    - for each group create **people [ ]**, a list of **struct person**  
    - for each person group[i].people create a  thread with thread function **simulate_group** and **&group_list[i]** as argument.
    - create **goal_list [ ]**, a list of **struct goal**
    - for each goal[i] create a thread with thread function **simulate_goal** and **&goal_list [ ]**
    - start timer with  **simulate_timer** having argument equal to max_time + 5 where **max_time**  when person comes to stadium
- **`encode_zone()`**
    - return enum integer corresponding to char zone.


## **group.c**
- **``increamenting_exiting_cnt()``**
    - increaments group_list [ group_number ].num_people_waiting_at_exit
    - called by person exiting the zone to exit gate
- **`simulate_group()`**
    - wait till time = 0
    - condition wait on till whole group is at exit gate
    - group exits simulation.



## **person.c**
- **`simulate_person()`**
    - wait till time = person's arrival time
    - wait till he gets a seat in his patience time 
    - if he doesn't get his seat he waits at the exit for his group.
    - if he gets a seat then watch for the **SPECATING_TIME_X** time and then go exit and wait for the group mates.


## **zone.c**
- **`increament_zone_cnt()`**
    - person is at ticket counter to get seat
    - check if a person is getting any seat in one of his eligible zones 
    - when a person gets seat in some zone check if the difference in time of getting the to ticket counter and his arrival is less than his patiance.
        - if yes print his allocated zone
        - else print "person could not get a seat"

- **`decreament_zone_cnt()`**
    - person leaving zone to exit gate
    - decreament **num_persons_zone_x**

## **goal.c**
- **`simulate_goal()`**
    - wait for the goal time
    - if **goal_x->probability** is more than **GOAL_PROBABILITY** , it is a goal
        - if goal is by home_team increament **home_team_score** else increament **away_team_score**
        - if **home_team_score** is greater then **away_team_score** 
            -  check if any away team fans who are present in stadium are enraged.
            - print appropriate message message 
        - else 
            -  check if any home team fans who are present in stadium are enraged.
            - print appropriate message message 
    - else 
        - goal missed the chance of becoming real one. ( print appropriate message )


## **stimer.c**
- **`simulate_timer()`**
    - for every one second **SIGALARM** is raised by **alarm(1)** and it is handled by a function **increament_timer()** function
- **`increament_timer()`**
    - increaments **stimer** by 1.
    - sends a broadcast signal to all threads waiting on **stimer_cond**.
