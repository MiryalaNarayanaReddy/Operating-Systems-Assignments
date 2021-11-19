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
using namespace std;

#define BBLACK      "\e[1;30m"
#define BRED        "\e[1;31m"
#define BGREEN      "\e[1;32m"
#define BYELLOW     "\e[1;33m"
#define BBLUE       "\e[1;34m"
#define BMAGNETA    "\e[1;35m"
#define BCYAN       "\e[1;36m"
#define RESET_COLOR "\x1b[0m"

typedef long long ll ;

#define pb push_back
#define debug(x) cout << #x << " : " << x << endl
#define part cout << "-----------------------------------" << endl;

///////////////////////////////
#define MAX_CLIENTS 4
#define PORT_ARG 8001

const int initial_msg_len = 256;

////////////////////////////////////

const ll buff_sz = 1048576;
///////////////////////////////////////////////////


pair<string, int> read_string_from_socket(const int &fd, int bytes);
int send_string_on_socket(int fd, const string &s);
void handle_connection(int client_socket_fd);


#endif