#ifndef __SERVER_SIM_H__
#define __SERVER_SIM_H__

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
#include <iostream>
#include <assert.h>
#include <tuple>
#include <map>
#include <pthread.h>
#include <queue>
#include <ctype.h>
#include <string>

using namespace std;

#define BBLACK "\e[1;30m"
#define BRED "\e[1;31m"
#define BGREEN "\e[1;32m"
#define BYELLOW "\e[1;33m"
#define BBLUE "\e[1;34m"
#define BMAGNETA "\e[1;35m"
#define BCYAN "\e[1;36m"
#define RESET_COLOR "\x1b[0m"

typedef long long ll;

#define pb push_back
#define debug(x) cout << #x << " : " << x << endl
#define part cout << "-----------------------------------" << endl;

///////////////////////////////
#define PORT_ARG 8001

const int initial_msg_len = 256;

////////////////////////////////////

const ll buff_sz = 1048576;
///////////////////////////////////////////////////
typedef struct client
{
    int client_socket_fd;
    struct sockaddr_in client_addr_obj;
} client;

extern map<int, string> dictionary;
extern queue<client> q;
extern pthread_mutex_t q_lock;
extern pthread_cond_t q_cond;
extern pthread_mutex_t dict_lock;
extern pthread_cond_t dict_cond;
extern pthread_mutex_t read_lock;
extern pthread_cond_t read_cond;

extern pthread_mutex_t write_lock;
extern pthread_cond_t write_cond;

///////////////////////////////////////////
pair<string, int> read_string_from_socket(const int &fd, int bytes);
int send_string_on_socket(int fd, const string &s);

void *handle_connection(void *arg);
// void handle_connection(int client_socket_fd);

#endif