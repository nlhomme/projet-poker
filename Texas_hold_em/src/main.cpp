#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <pthread.h>

#include "Services.h"

using namespace std;

int main(int argc, char *argv[])
{
    /*créer les thread serveur et messagerie*/
    pthread_t* server_thread;
    pthread_t* client_thread;
    server_thread = Services::thread_server();
    client_thread = Services::thread_messenger();

    /*synchronisation de threads, attend la fin des threads pour continuer le programmes*/
    pthread_join(*server_thread, NULL);
    pthread_join(*lclient_thread, NULL);
}
