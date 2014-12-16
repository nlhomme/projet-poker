#include "Socket.h"

using namespace std;

void Socket::clientSocket()
{
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


void Socket::serverSocket()
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
