/*******
    Florent Baudon
*******/
#include "Socket.h"
#include "Services.h"

using namespace std;

void Socket::clientSocket(string msg, string hostname)
{
    //déclaration de la socket
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == INVALID_SOCKET)
    {
        cout << "INVALID SOCKET" << endl;

        exit(EXIT_FAILURE);
    }

    struct hostent *hostinfo = NULL;
    SOCKADDR_IN sin = {0}; //initialise la structutre avec des zeros

    inet_aton(hostname.c_str(), &sin.sin_addr);
/*
    hostinfo = gethostbyname(hostname.c_str());
    cout << "ip : " + hostname + " / " + hostinfo->h_addr << endl;

    if(hostinfo == NULL)
    {
        cout << "Unknown host :" << hostname << endl;
        exit(EXIT_FAILURE);
    }

    sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr; //adresse*/
    sin.sin_port = htons(PORT);
    sin.sin_family = AF_INET;

    if(connect(sock, (SOCKADDR *) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
    {
        cout << "Failed to connect" << endl;
        exit(EXIT_FAILURE);
    }

    const char *buffer = msg.c_str();
    if(send(sock, buffer, 150, 0) < 0){
        cout << "Error send" << endl;
        exit(EXIT_FAILURE);
    }
}


int Socket::serverSocket()
{
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

    /*Stop sur cette fonction pour l'écoute*/
    while(true)
    {
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
            //exit(EXIT_FAILURE);
            return 0;
        }

        buffer[n] = '\0';

        //remonte le message sur la couche services
        ServicesSocket::receivedMessage(buffer);
        //l'ajoute dans le tableau
        ServicesSocket::addMessage(buffer);
        //cout << "message : " << buffer << endl;
    }

    closesocket(sock);
    closesocket(csock);

    return 1;
}

string Socket::getMyIp()
{
     int fd;
     struct ifreq ifr;

     fd = socket(AF_INET, SOCK_DGRAM, 0);

     /* I want to get an IPv4 IP address */
     ifr.ifr_addr.sa_family = AF_INET;

     /* I want IP address attached to "eth0" */
     strncpy(ifr.ifr_name, "eth0", IFNAMSIZ-1);

     ioctl(fd, SIOCGIFADDR, &ifr);

     close(fd);

     /* display result */
     printf("%s\n", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
}
