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
#include <unistd.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <string.h>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

#define GROUP "226.1.1.1"
#define PORTMULTICAST 4321

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;


class Multicast
{
    public:
        /*Serveur multicast qui emet à tout les membres du groupe*/
        static void serverMulti();
        /*Client multi cast qui recoit les message (contenant les adresses) du groupe*/
        static std::string clientMulti();
        /*fonction messenger*/
        static void messenger(std::string message);
        /*Permet d'éditer la variabel m_name*/
        static void setPlayerName(std::string name);
        static std::string getPlayerName();
        /*Fonction permettant de récupérer l'adresse ip*/
        static std::string getLocalAddress();
    private :
        /*attribut statique stokant le nom du joueur*/
        static std::string m_name;
};

#endif // MULTICAST_H
