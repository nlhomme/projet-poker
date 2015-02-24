/*******
    Florent Baudon
*******/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <pthread.h>

#include "Multicast.h"
#include "Services.h"
#include "Socket.h"
#include "DiscoverProtocol.h"

using namespace std;

int main(int argc, char *argv[])
{
    string playerName;
    getline(cin, playerName);
    Multicast::setPlayerName(playerName);

    DiscoverProtocol* dp = new DiscoverProtocol();
    dp->startDiscover();
    //dp->stopDiscover();

    //test multicast
    /*string playerName;
    cout << "Player name : " << endl;
    getline(cin, playerName);
    ServicesMulticast::setPlayerName(playerName);

    pthread_t thread_list = ServicesMulticast::threadListener();
    ServicesMulticast::sendMulticast();

    pthread_t thread_getmsg;
    pthread_create(&thread_getmsg, NULL, [](void* arg)->void*{
                       while(true)
                       {
                        string msg = ServicesMulticast::getMessage();
                           if(!msg.empty())
                           {
                                cout << msg << endl;
                           }
                       }
                    }, NULL);

    while(true)
    {

        string message;
        getline(cin, message);
        ServicesMulticast::multicastMessenger(message);

    }

    pthread_cancel(thread_list);*/

    //test message plus chat
    /*string hostname;
    cout << "test serveur 1 ---- client 2 ";
    getline(cin, hostname);

    if(hostname == "1")
    {
            Multicast::serverMulti();
    }else
    {
            Multicast::clientMulti();
    }*/
    /*string hostname;
    cout << "Hostname : ";
    getline(cin, hostname);
    ServicesSocket::setHostname(hostname);

    ServicesSocket::thread_server();
    /*Service de chat*/
    /*ServicesSocket::thread_messenger();
    string msg;
    getline(cin, msg);
    /*Envoie UN message*/
    //ServicesSocket::sendAMessage(msg);

    /*pour pour récupérer un message en continu
    fair ça avec un thread ?*/
   /*while(true){
        string msg = ServicesSocket::getMessage(); /*récupére un message*/
        /*if(!msg.empty())
        {
            cout << msg << endl;
        }
    }*/

}
