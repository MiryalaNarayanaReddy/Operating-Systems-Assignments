#include "server_sim.h"

map<int, string> dictionary;
queue<client> q;
int MAX_CLIENTS;

pthread_mutex_t q_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t q_cond = PTHREAD_COND_INITIALIZER;

pthread_mutex_t dict_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t dict_cond = PTHREAD_COND_INITIALIZER;

pthread_mutex_t read_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t read_cond = PTHREAD_COND_INITIALIZER;

pthread_mutex_t write_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t write_cond = PTHREAD_COND_INITIALIZER;

int main(int argc, char *argv[])
{
    int num_worker_threads = atoi(argv[1]);
    MAX_CLIENTS = num_worker_threads;
    printf("%s\n", argv[1]);
    cout << num_worker_threads << "\n";
    // make handle threads
    pthread_t worker_tid[num_worker_threads];
    for (int i = 0; i < num_worker_threads; i++)
    {
        pthread_create(&worker_tid[i], NULL, handle_connection, NULL);
        cout << worker_tid[i] << "\n";
    }

    int wel_socket_fd, client_socket_fd, port_number;
    socklen_t clilen;

    struct sockaddr_in serv_addr_obj, client_addr_obj;
    /////////////////////////////////////////////////////////////////////////
    /* create socket */
    /*
    The server program must have a special door—more precisely,
    a special socket—that welcomes some initial contact
    from a client process running on an arbitrary host
    */
    //get welcoming socket
    //get ip,port
    /////////////////////////
    wel_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (wel_socket_fd < 0)
    {
        perror("ERROR creating welcoming socket");
        exit(-1);
    }

    //////////////////////////////////////////////////////////////////////
    /* IP address can be anything (INADDR_ANY) */
    bzero((char *)&serv_addr_obj, sizeof(serv_addr_obj));
    port_number = PORT_ARG;
    serv_addr_obj.sin_family = AF_INET;
    // On the server side I understand that INADDR_ANY will bind the port to all available interfaces,
    serv_addr_obj.sin_addr.s_addr = INADDR_ANY;
    serv_addr_obj.sin_port = htons(port_number); //process specifies port

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    /* bind socket to this port number on this machine */
    /*When a socket is created with socket(2), it exists in a name space
       (address family) but has no address assigned to it.  bind() assigns
       the address specified by addr to the socket referred to by the file
       descriptor wel_sock_fd.  addrlen specifies the size, in bytes, of the
       address structure pointed to by addr.  */

    //CHECK WHY THE CASTING IS REQUIRED
    if (bind(wel_socket_fd, (struct sockaddr *)&serv_addr_obj, sizeof(serv_addr_obj)) < 0)
    {
        perror("Error on bind on welcome socket: ");
        exit(-1);
    }
    //////////////////////////////////////////////////////////////////////////////////////

    /* listen for incoming connection requests */

    listen(wel_socket_fd, MAX_CLIENTS);
    cout << "Server has started listening on the LISTEN PORT" << endl;
    clilen = sizeof(client_addr_obj);
    client client_x;
    while (1)
    {
        /* accept a new request, create a client_socket_fd */
        /*
        During the three-way handshake, the client process knocks on the welcoming door
        of the server process. When the server “hears” the knocking, it creates a new door—
        more precisely, a new socket that is dedicated to that particular client.
        */
        //accept is a blocking call

        printf("Waiting for a new client to request for a connection\n");
        client_x.client_socket_fd = accept(wel_socket_fd, (struct sockaddr *)&client_x.client_addr_obj, &clilen);
        if (client_x.client_socket_fd < 0)
        {
            perror("ERROR while accept() system call occurred in SERVER");
            exit(-1);
        }

        printf(BGREEN "New client connected from port number %d and IP %s \n" RESET_COLOR, ntohs(client_x.client_addr_obj.sin_port), inet_ntoa(client_x.client_addr_obj.sin_addr));

        pthread_mutex_lock(&q_lock);
        q.push(client_x);
        pthread_cond_signal(&q_cond);
        pthread_mutex_unlock(&q_lock);
        // sleep(2);
        // handle_connection(client_socket_fd);
        // cout << "client---\n";
    }

    close(wel_socket_fd);
    return 0;
}
