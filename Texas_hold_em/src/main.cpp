#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Socket.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Client ou serveur ? \n 1 - Serveur \n 2 - Client" << endl;
    int choice;
    cin >> choice;
    cin.ignore();

    if(choice == 1)
    {
        Socket::serverSocket();
    }
    else if (choice == 2)
    {
        /*Demande du hostname du receveur*/
        cout << "Hostname :" << endl;
        string hostname;
        getline(cin,hostname);

        while(true){
            /*demande du message*/
            cout << "message :";
            string msg;
            getline(cin,msg);
            cout <<" " << endl;

            Socket::clientSocket(msg, hostname);
        }
    }
}
