/*******
    Florent Baudon
*******/

#ifndef MULTICAST_H
#define MULTICAST_H

#include <stdlib.h>
#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <ifaddrs.h>
#include <stdio.h>
#include <string.h>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

#define GROUP "226.1.1.1"
#define PORT 4321

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;


class Multicast
{
    public:
        /*Serveur multicast qui emet à tout les membres du groupe*/
        static void serverMulti();
        /*Client multi cast qui recoit les message (contenant les adresses) du groupe*/
        static void clientMulti();
    private :
        static std::string getLocalAddress();
        static std::string m_name;
};

#endif // MULTICAST_H
