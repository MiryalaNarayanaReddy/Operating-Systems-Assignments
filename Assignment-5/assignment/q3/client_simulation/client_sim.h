#ifndef __CLIENT_SIM_H__
#define __CLIENT_SIM_H__

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

/////////////////////////////
#include <pthread.h>
#include <iostream>
#include <semaphore.h>
#include <assert.h>
#include <queue>
#include <vector>
#include <tuple>

#include "stimer.h"

using namespace std;

/////////////////////////////

#define BBLACK "\e[1;30m"
#define BRED "\e[1;31m"
#define BGREEN "\e[1;32m"
#define BYELLOW "\e[1;33m"
#define BBLUE "\e[1;34m"
#define BMAGNETA "\e[1;35m"
#define BCYAN "\e[1;36m"
#define RESET_COLOR "\x1b[0m"

typedef long long ll;
const ll MOD = 1000000007;
#define part cout << "-----------------------------------" << endl;
#define pb push_back
#define debug(x) cout << #x << " : " << x << endl

///////////////////////////////
#define SERVER_PORT 8001
////////////////////////////////////

const ll buff_sz = 1048576;
///////////////////////////////////////////////////

extern int SOCKET_FD;

typedef struct client
{
    int indx;
    int time;
    string msg;
    pthread_t tid;
    int socket_fd;
} client;

pair<string, int> read_string_from_socket(int fd, int bytes);
int send_string_on_socket(int fd, const string &s);
// int get_socket_fd(struct sockaddr_in *ptr, int port_num);
int get_socket_fd(struct sockaddr_in *ptr);
void *send_msg(void *arg);

#endif
