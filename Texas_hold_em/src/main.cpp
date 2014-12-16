#include <stdio.h>
#include <stdlib.h>
#include <iostream>



#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
#define PORT    25000

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

using namespace std;

void createSocketClient(){

    cout << "CLIENT" << endl;
    //déclaration de la socket
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == INVALID_SOCKET)
    {
        cout << "INVALID SOCKET" << endl;

        exit(EXIT_FAILURE);
    }

    struct hostent *hostinfo = NULL;
    SOCKADDR_IN sin = {0}; //initialise la structutre avec des zeros

    //const char *hostname = "127.0.0.1";
    string hostname;
    cout << "Adresse IP : ";
    cin >> hostname;

    hostinfo = gethostbyname(hostname.c_str());
    if(hostinfo == NULL)
    {
        cout << "Unknown host :" << hostname << endl;
        exit(EXIT_FAILURE);
    }

    sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr; //adresse
    sin.sin_port = htons(PORT);
    sin.sin_family = AF_INET;

    if(connect(sock, (SOCKADDR *) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
    {
        cout << "Failed to connect" << endl;
        exit(EXIT_FAILURE);
    }

    const char *buffer = "Bonjour !";
    if(send(sock, buffer, 9, 0) < 0){
        cout << "Error send" << endl;
        exit(EXIT_FAILURE);
    }

}

void createSocketServer()
{
    cout << "SERVER" << endl;
    //déclaration de la socket
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == INVALID_SOCKET)
    {
        cout << "INVALID SOCKET" << endl;

        exit(EXIT_FAILURE);
    }
    SOCKADDR_IN sin = { 0 };

    sin.sin_addr.s_addr = htonl(INADDR_ANY); /* nous sommes un serveur, nous acceptons n'importe quelle adresse */

    sin.sin_family = AF_INET;

    sin.sin_port = htons(PORT);

    if(bind (sock, (SOCKADDR *) &sin, sizeof sin) == SOCKET_ERROR)
    {
        perror("bind()");
        exit(EXIT_FAILURE);
    }

    //écoute des connexions
    if(listen(sock, 5) == SOCKET_ERROR)
    {
        perror("listen()");
        exit(EXIT_FAILURE);
    }


    SOCKADDR_IN csin = { 0 };
    SOCKET csock;

    socklen_t sinsize = sizeof csin;

    csock = accept(sock, (SOCKADDR *)&csin, &sinsize);

    if(csock == INVALID_SOCKET)
    {
        perror("accept()");
        exit(EXIT_FAILURE);
    }

    //lecture du ms client
    char buffer[1024];
    int n = 0;

    if((n = recv(csock, buffer, sizeof buffer - 1, 0)) < 0)
    {
        perror("recv()");
        exit(EXIT_FAILURE);
    }

    buffer[n] = '\0';

    cout << "message : " << buffer << endl;

    closesocket(sock);
    closesocket(csock);
}

int main(int argc, char *argv[])
{
    cout << "Client ou serveur ? \n 1 - Serveur \n 2 - Client" << endl;
    int choice;
    cin >> choice;

    if(choice == 1)
        createSocketServer();
    else if (choice == 2)
        createSocketClient();
}
