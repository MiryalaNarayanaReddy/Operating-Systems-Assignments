# Multithreaded client and server

## ***Client simulation***
[client_simulation](client_simulation) folder contains the code for simulating multiple clients using threads.

folder structure

```
client_simulation
    |
    |
    |______ client_sim.cpp & client_sim.h
    |
    |______ stimer.cpp & stimer.h
    |
    |_______ main.cpp
    |
    |_______ Makefile
    |
    |_______ i.txt

```

### **main.cpp** 

- declares and initalizes global mutex locks and conditions.
- creates vector of m clients ( client is a struct ).
    - for each client its struct values are scaned from input and a thread is created for this client.
    - thread creation uses `handle_client()` funtion with `client` passed an argument.
- To start simulation, `simulate_timer()` function is used which takes time of simulation as argument.
- finally all threads are joined and main exits.

### **client_sim.cpp**

This has the following functions:
    
- `read_string_from_socket() :`
    - This is called by clients when they are reading messages from server. ( **read_lock** is used to avoid  multiple threads accessing the body of this function)
- `send_string_on_socket() :` 
    - This is called by clients when they are writing messages to server. ( **write_lock** is used to avoid  multiple threads accessing the body of this function)
- `get_socket_fd() :`
    - This is called by clients when they connecting to server. ( **get_fd_lock** is used to avoid  multiple threads accessing the body of this function)

- `simulate_client() :`
    - This is the function executed by each thread ( **client** ).
    - Main steps in this function are :
        - wait for the **stimer** to be client time ( using conditional wait on **stimer_cond** )
        - connect to server ( using `get_socket_fd()` )
        - send message    ( using `send_string_on_socket()` )
        - recieve message  ( using `read_string_from_socket()` )
        - send exit message 

---------

## ***Server simulation***

[server_simulation](server_simulation) folder conatains code for simulating a server which listens to clients and puts them in a queue from which the worker threads take one client and process respective clients' requests'.

folder structure

```
server_simulation
    |
    |
    |______ server_sim.cpp & server_sim.h
    |
    |_______ main.cpp
    |
    |_______ Makefile
    |
    |_______ i.txt

```

### **main.cpp**
- declares and initalizes global mutex locks and conditions
- declare dictionary as map of int and string and queue of clients
- creates n ( = argv[1]) worker threads
- starts the server and listens for clients.
- for each client it accepts, it pushes it into the queue of clients and sends a condition signal. only one thread will wake up and pop() the client from the queue and serve it.

### **server_sim.cpp**

This has the following functions:
    
- `read_string_from_socket() :`
    - This is called by handle_connection() when they are reading messages from server. ( **read_lock** is used to avoid  multiple threads accessing the body of this function)

- `send_string_on_socket() :` 
    - This is called by handle_connection() when they are writing messages to server. ( **write_lock** is used to avoid  multiple threads accessing the body of this function)

- `handle_connection() :`
    - This is the function executed by each thread ( worker threads in thread_pool ).
    - Main steps in this function are :
        - wait for the **queue** to be non empty ( using conditional wait on **q_cond** )
        - pop the client and provide service to it
        - recieve message  ( using `read_string_from_socket()` )
        - process the command and modify the dictionary accordingly (uses **dict_lock**)
        - send acknowledgement message ( using `send_string_on_socket()` )


-----------
