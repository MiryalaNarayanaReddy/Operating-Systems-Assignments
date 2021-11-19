#include "server_sim.h"

pair<string, int> read_string_from_socket(const int &fd, int bytes)
{
    std::string output;
    output.resize(bytes);

    int bytes_received = read(fd, &output[0], bytes - 1);
    debug(bytes_received);
    if (bytes_received <= 0)
    {
        cerr << "Failed to read data from socket. \n";
    }

    output[bytes_received] = 0;
    output.resize(bytes_received);
    // debug(output);
    return {output, bytes_received};
}

int send_string_on_socket(int fd, const string &s)
{
    // debug(s.length());
    int bytes_sent = write(fd, s.c_str(), s.length());
    if (bytes_sent < 0)
    {
        cerr << "Failed to SEND DATA via socket.\n";
    }

    return bytes_sent;
}

///////////////////////////////

// void *handle_connection(void *arg)
// {
//     // int client_socket_fd = *((int *)client_socket_fd_ptr);
//     //####################################################

//     int received_num, sent_num, client_socket_fd;

//     /* read message from client */
//     int ret_val = 1;
//     while (true)
//     {
//         // check for queue empty or not
//         pthread_mutex_lock(&q_lock);
//         while (q.empty())
//         {
//             pthread_cond_wait(&q_cond, &q_lock);
//         }
//         client_socket_fd = q.front().socket_fd;
//         pthread_mutex_unlock(&q_lock);
//         while (true)

//             while (true)
//             {
//                 string cmd;
//                 tie(cmd, received_num) = read_string_from_socket(client_socket_fd, buff_sz);
//                 ret_val = received_num;
//                 // debug(ret_val);
//                 // printf("Read something\n");
//                 if (ret_val <= 0)
//                 {
//                     // perror("Error read()");
//                     printf("Server could not read msg sent from client\n");
//                     break;
//                 }
//                 cout << "Client sent : " << cmd << endl;
//                 if (cmd == "exit")
//                 {
//                     cout << "Exit pressed by client" << endl;
//                     break;
//                 }
//                 // process the command
//                 // wait for 2 second
//                 // sleep(2);
//                 string msg_to_send_back = "Ack: " + to_string(pthread_self()) + " " + cmd;

//                 ////////////////////////////////////////
//                 // "If the server write a message on the socket and then close it before the client's read. Will the client be able to read the message?"
//                 // Yes. The client will get the data that was sent before the FIN packet that closes the socket.

//                 int sent_to_client = send_string_on_socket(client_socket_fd, msg_to_send_back);
//                 // debug(sent_to_client);
//                 if (sent_to_client == -1)
//                 {
//                     perror("Error while writing to client. Seems socket has been closed");
//                     break;
//                 }
//             }
//     }
//     close(client_socket_fd);
//     printf(BRED "Disconnected from client" RESET_COLOR "\n");
//     // return NULL;
// }




void handle_connection(int client_socket_fd)
{
    // int client_socket_fd = *((int *)client_socket_fd_ptr);
    //####################################################

    int received_num, sent_num;

    /* read message from client */
    int ret_val = 1;

    while (true)
    {
        string cmd;
        tie(cmd, received_num) = read_string_from_socket(client_socket_fd, buff_sz);
        ret_val = received_num;
        // debug(ret_val);
        // printf("Read something\n");
        if (ret_val <= 0)
        {
            // perror("Error read()");
            printf("Server could not read msg sent from client\n");
            goto close_client_socket_ceremony;
        }
        cout << "Client sent : " << cmd << endl;
        if (cmd == "exit")
        {
            cout << "Exit pressed by client" << endl;
            goto close_client_socket_ceremony;
        }
        string msg_to_send_back = "Ack: " + cmd;

        ////////////////////////////////////////
        // "If the server write a message on the socket and then close it before the client's read. Will the client be able to read the message?"
        // Yes. The client will get the data that was sent before the FIN packet that closes the socket.

        int sent_to_client = send_string_on_socket(client_socket_fd, msg_to_send_back);
        // debug(sent_to_client);
        if (sent_to_client == -1)
        {
            perror("Error while writing to client. Seems socket has been closed");
            goto close_client_socket_ceremony;
        }
    }

close_client_socket_ceremony:
    close(client_socket_fd);
    printf(BRED "Disconnected from client" RESET_COLOR"\n");
    // return NULL;
}
