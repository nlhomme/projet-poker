#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <pthread.h>
#include "Socket.h"

using namespace std;

void startFunction()
{
    pthread_t thread1;
    pthread_create(&thread1, NULL, &Socket::serverSocket, NULL);
}

int main(int argc, char *argv[])
{
    startFunction();
    /*cout << "Client ou serveur ? \n 1 - Serveur \n 2 - Client" << endl;
    int choice;
    cin >> choice;
    cin.ignore();

    if(choice == 1)
    {
        Socket::serverSocket();
    }
    else if (choice == 2)
    {*/
        /*Demande du hostname du receveur*/
        cout << "Hostname :" << endl;
        string hostname;
        getline(cin,hostname);

        bool exit = false;

        while(!exit){
            /*demande du message*/
            cout << "message :";
            string msg;
            getline(cin,msg);

            if(!msg.compare("exit"))
            {
                Socket::clientSocket("Client à quitté la conversation", hostname);
                cout << "Arrêt de la conversation" << endl;
                exit = true;
            }else
            {
                Socket::clientSocket(msg, hostname);
            }
        }
    //}
}
