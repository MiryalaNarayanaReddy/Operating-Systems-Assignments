#include "client_sim.h"

////////////////////////// START OF TUTORIAL CODE ////////////////////////////
pair<string, int> read_string_from_socket(int fd, int bytes)
{
    std::string output;
    output.resize(bytes);

    int bytes_received = read(fd, &output[0], bytes - 1);
    // debug(bytes_received);
    if (bytes_received <= 0)
    {
        cerr << "Failed to read data from socket. Seems server has closed socket\n";
        // return "
        exit(-1);
    }

    // debug(output);
    output[bytes_received] = 0;
    output.resize(bytes_received);

    return {output, bytes_received};
}

int send_string_on_socket(int fd, const string &s)
{
    // cout << "We are sending " << s << endl;
    int bytes_sent = write(fd, s.c_str(), s.length());
    // debug(bytes_sent);
    // debug(s);
    if (bytes_sent < 0)
    {
        cerr << "Failed to SEND DATA on socket.\n";
        // return "
        exit(-1);
    }

    return bytes_sent;
}

int get_socket_fd(struct sockaddr_in *ptr)
{
    struct sockaddr_in server_obj = *ptr;

    // socket() creates an endpoint for communication and returns a file
    //        descriptor that refers to that endpoint.  The file descriptor
    //        returned by a successful call will be the lowest-numbered file
    //        descriptor not currently open for the process.
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0)
    {
        perror("Error in socket creation for CLIENT");
        exit(-1);
    }
    /////////////////////////////////////////////////////////////////////////////////////
    int port_num = SERVER_PORT;

    memset(&server_obj, 0, sizeof(server_obj)); // Zero out structure
    server_obj.sin_family = AF_INET;
    server_obj.sin_port = htons(port_num); //convert to big-endian order

    // Converts an IP address in numbers-and-dots notation into either a
    // struct in_addr or a struct in6_addr depending on whether you specify AF_INET or AF_INET6.
    //https://stackoverflow.com/a/20778887/6427607

    /////////////////////////////////////////////////////////////////////////////////////////
    /* connect to server */

    if (connect(socket_fd, (struct sockaddr *)&server_obj, sizeof(server_obj)) < 0)
    {
        perror("Problem in connecting to the server");
        exit(-1);
    }

    //part;
    // printf(BGREEN "Connected to server\n" RESET_COLOR);
    // part;
    return socket_fd;
}
////////////////////////// END OF TUTORIAL CODE ///////////////////////////////

void *send_msg(void *arg)
{

    client *client_x = (client *)arg;
    // cout << "Connection to server successful" << endl;
    // cout << "Enter msg: ";

    pthread_mutex_lock(&stimer_lock);
    while (stimer != client_x->time)
    {
        pthread_cond_wait(&stimer_cond, &stimer_lock);
    }
    pthread_mutex_unlock(&stimer_lock);

    send_string_on_socket(SOCKET_FD, client_x->msg);
    int num_bytes_read;
    string output_msg;
    tie(output_msg, num_bytes_read) = read_string_from_socket(SOCKET_FD, buff_sz);
    cout << BRED << client_x->indx << " : " << RESET_COLOR << BGREEN << output_msg << RESET_COLOR << "\n";
    // part;
    return NULL;
}
