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

    if(choice == 1)
        Socket::serverSocket();
    else if (choice == 2)
        Socket::clientSocket();
}
