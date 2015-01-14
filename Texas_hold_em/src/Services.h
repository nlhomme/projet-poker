#ifndef SERVICES_H
#define SERVICES_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <pthread.h>

class Services
{
    public :
        static pthread_t thread_server();
        static pthread_t thread_messenger();
        static void receivedMessage(std::string msg); /*permet au service de récupérer les messages envoyer par Socket*/
        static std::string getMessage(); /*Permet à une couche supérieur de récupérer les messages récupérer par Services*/
    private :
        static void* startServer(void* arg);
        static void* sendMessenger(void* arg);

        static std::string message;
};

#endif // SERVICES_H
