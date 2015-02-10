/*******
    Florent Baudon
*******/

#ifndef SERVICES_H
#define SERVICES_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <pthread.h>

class ServicesSocket
{
    public :
        static pthread_t thread_server();
        static void sendAMessage(std::string msg);
        static pthread_t thread_messenger();
        static void receivedMessage(std::string msg); /*permet au service de récupérer les messages envoyer par Socket*/
        static std::string getMessage(); /*Permet à une couche supérieur de récupérer les messages récupérer par Services*/
        static void setHostname(std::string hostname);

    private :
        static void* startServer(void* arg);
        static void* sendMessenger(void* arg);

        static std::string message;
        static std::string hostname;
};

class ServicesMulticast
{
    public :
        static void setPlayerName(std::string name);
        static pthread_t threadListener();
        static void sendMulticast();
        //static vector<std::string> playerList;
    private :
        static void* startListener(void* arg);
};

#endif // SERVICES_H
