/*******
    Florent Baudon
*******/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <pthread.h>
#include "multicast.cpp"

#include "Services.h"

using namespace std;

int main(int argc, char *argv[])
{
    string hostname;
        cout << "test serveur 1 ---- client 2 ";
    getline(cin, hostname);
    if(hostname == "1")
    {
            emission();
    }else
    {
            reception();
    }
    /*string hostname;
    cout << "Hostname : ";
    getline(cin, hostname);
    Services::setHostname(hostname);

    Services::thread_server();
    /*Service de chat*/
    /*Services::thread_messenger();
    string msg;
    getline(cin, msg);
    /*Envoie UN message*/
    //Services::sendAMessage(msg);

    /*pour pour récupérer un message en continu
    fair ça avec un thread ?*/
   /* while(true){
        string msg = Services::getMessage(); /*récupére un message*/
        /*if(!msg.empty())
        {
            cout << msg << endl;
        }
    }*/

}
