#include "client_sim.h"
#include "stimer.h"

int stimer = -1;
pthread_mutex_t stimer_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t stimer_cond = PTHREAD_COND_INITIALIZER;
sem_t read_mutex;
sem_t write_mutex;
int SOCKET_FD;

int main()
{
    sem_init(&read_mutex,0,1);
    sem_init(&write_mutex,0,1);
    struct sockaddr_in server_obj;
    SOCKET_FD = get_socket_fd(&server_obj);

    int m;
    string temp;
    cin >> m;
    getline(cin, temp);

    vector<client> client_list(m);
    for (int i = 0; i < m; i++)
    {
        client_list[i].indx = i;
        cin >> client_list[i].time;
        getline(cin, client_list[i].msg);
        client_list[i].msg.erase(0, 1);
        cout << "-" << client_list[i].msg << "-\n";
        pthread_create(&client_list[i].tid, NULL, send_msg, (void *)&client_list[i]);
        // sleep(3);
    }

    cout << "Starting the Simulation of clients...\n";
    simulate_timer(client_list[m - 1].time+5);
    for (int i = 0; i < m; i++)
    {
        pthread_tryjoin_np(client_list[i].tid, NULL);
    }
    sem_destroy(&read_mutex);
    sem_destroy(&write_mutex);
    return 0;
}