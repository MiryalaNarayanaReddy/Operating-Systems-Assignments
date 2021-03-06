#include "client_sim.h"
#include "stimer.h"

int stimer = -1;
pthread_mutex_t stimer_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t stimer_cond = PTHREAD_COND_INITIALIZER;

pthread_mutex_t get_fd_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t get_fd_cond = PTHREAD_COND_INITIALIZER;

pthread_mutex_t read_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t read_cond = PTHREAD_COND_INITIALIZER;

pthread_mutex_t write_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t write_cond = PTHREAD_COND_INITIALIZER;

int main()
{
    // struct sockaddr_in server_obj;
    // SOCKET_FD = get_socket_fd(&server_obj);

    int m;
    string temp;
    cin >> m;
    getline(cin, temp);

    vector<client> client_list(m);
    for (int i = 0; i < m; i++)
    {
        client_list[i].indx = i;
        cin >> client_list[i].time; // time
        getline(cin, client_list[i].msg);
        client_list[i].msg.erase(0, 1); // remove the space at the begining
        // cout << "-" << client_list[i].msg << "-\n";
        pthread_create(&client_list[i].tid, NULL, simulate_client, (void *)&client_list[i]);
        // sleep(3);
    }

    // cout << "Starting the Simulation of clients...\n";
    simulate_timer(client_list[m - 1].time + 2);
    for (int i = 0; i < m; i++)
    {
        pthread_join(client_list[i].tid, NULL);
    }

    return 0;
}