#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <pthread.h>

#include "Services.h"

using namespace std;

int main(int argc, char *argv[])
{
    /*créer les thread serveur et messagerie*/
    pthread_t server_thread;
    pthread_t client_thread;

    /*lance les threads*/
    pthread_create(&server_thread, NULL, &Services::sendMessenger, NULL);
    pthread_create(&client_thread, NULL, &Services::startServer, NULL);

    /*synchronisation de threads, attend la fin des threads pour continuer le programmes*/
    pthread_join(server_thread, NULL);
    pthread_join(client_thread, NULL);
}
