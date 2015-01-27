/*

multicast.c

The following program sends or receives multicast packets. If invoked
with one argument, it sends a packet containing the current time to an
arbitrarily chosen multicast group and UDP port. If invoked with no
arguments, it receives and prints these packets. Start it as a sender on
just one host and as a receiver on all the other hosts

*/

#include <stdlib.h>
#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#define GROUP "239.137.194.111"
#define PORT 55555

static void serverMulti()
{
    int sock;
    struct in_addr ip;
    static struct sockaddr_in ad_multicast, adresse;
    //décrit le groupe multicast
    ip_mreq gr_multicast;

    //creation du socket UDP
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    //récupération de l'adresse IP du groupe
    inet_aton("226.1.2.3", &ip);

    //cré   ation de l'indentificateur du groupe
    gr_multicast.imr_multiaddr.s_addr = ip.s_addr;
    gr_multicast.imr_interface.s_addr = htons(INADDR_ANY);

    //abonnement des la socket au groupe multicast
    setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &gr_multicast, sizeof(struct ip_mreq));

    //autorise la réutilisation du socket pour lier plusieurs socket sur le port
    int reuse = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (int*)&reuse, sizeof(reuse));

    //liaison socket au port du groupe multicast
    bzero((char*) &adresse, sizeof(adresse));
    ad_multicast.sin_family = AF_INET;
    ad_multicast.sin_addr.s_addr = htons(INADDR_ANY);
    ad_multicast.sin_port = htons(6234); //port à changer
    bind(sock, (struct sockaddr *) &adresse, sizeof(struct sockaddr_in));

    //emission du paquet
    static struct sockaddr_in adresseEmit ;
    int longueur_adresse = sizeof(struct sockaddr_in);
    bzero((char*) &adresse, sizeof(adresse));
    adresseEmit.sin_family = AF_INET;
    adresseEmit.sin_addr.s_addr = ip.s_addr;
    adresseEmit.sin_port = htons(6234);

    const char* message = "Bonjour !";

    sendto(sock, message, sizeof(message), 0, (struct sockaddr*)&adresseEmit, longueur_adresse);

}


static void clientmulti()
{
    int sock;
    struct in_addr ip;
    static struct sockaddr_in ad_multicast, adresse;
    //décrit le groupe multicast
    ip_mreq gr_multicast;

    //creation du socket UDP
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    //récupération de l'adresse IP du groupe
    inet_aton("226.1.2.3", &ip);

    //cré   ation de l'indentificateur du groupe
    gr_multicast.imr_multiaddr.s_addr = ip.s_addr;
    gr_multicast.imr_interface.s_addr = htons(INADDR_ANY);

    //abonnement des la socket au groupe multicast
    setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &gr_multicast, sizeof(struct ip_mreq));

    //autorise la réutilisation du socket pour lier plusieurs socket sur le port
    int reuse = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (int*)&reuse, sizeof(reuse));

    //liaison socket au port du groupe multicast
    bzero((char*) &adresse, sizeof(adresse));
    ad_multicast.sin_family = AF_INET;
    ad_multicast.sin_addr.s_addr = htons(INADDR_ANY);
    ad_multicast.sin_port = htons(6234); //port à changer
    bind(sock, (struct sockaddr *) &adresse, sizeof(struct sockaddr_in));

    char buffer[1024];
    while(true)
    {
        recv(sock, buffer, 1000, 0);
        std::cout << buffer << std::endl;
    }
}

static int reception()
{
        string addresse_ip = "127.0.0.1";

        struct ip_mreq imr;
        int sock_channel;
        struct sockaddr_in m_socketAddr;
        const char * multicastIPaddr;
        unsigned short port = 55000;
        int len;
        struct sockaddr_in remote_addr;
        socklen_t remote_addr_len = sizeof(struct sockaddr_in);
        unsigned char recv_buffer[9000];
        multicastIPaddr = GROUP;

        // open the socket
        sock_channel = socket(PF_INET, SOCK_DGRAM, 0);
        if(sock_channel < 0)
        {
                perror("Can't open the receive socket\n");
                exit(1);
        }

        // initialize the channel
        bzero(&m_socketAddr, sizeof(m_socketAddr));
        m_socketAddr.sin_family = AF_INET;
        m_socketAddr.sin_port = port;
        if(inet_aton(addresse_ip, &(m_socketAddr.sin_addr))<0)
        {
                perror("cannot get the locale IP address for 192.168.18.15 \n");
                exit(1);
        }
        int one = 1;
        if(setsockopt(sock_channel, SOL_SOCKET, SO_REUSEADDR, (char *)&one, sizeof(one))<0)
        {
                perror("Error in reusing addr\n");
                exit(1);
        }

        // creation of the link between the socket and its port
        if (bind(sock_channel, (struct sockaddr *)&m_socketAddr,
                sizeof(m_socketAddr)) < 0)
        {
                perror("problem blablzawith function bind errno \n");
                exit(1);
        }

        // activation of the multicast
        memset(&imr, 0, sizeof(struct ip_mreq));
        if(inet_aton(multicastIPaddr, (struct in_addr*)&(imr.imr_multiaddr.s_addr))<0)
        {
                perror("cannot get the multicast IP address for 239.137.194.111\n");
                exit(1);
        }
        if(inet_aton(addresse_ip, (struct in_addr*)&(imr.imr_interface.s_addr))<0)
        {
                perror("cannot get the local IP address for multicast interface 192.168.18.15 \n");
                exit(1);
        }
        if (setsockopt(sock_channel, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *)&imr,
                                                        sizeof(struct ip_mreq)) < 0)
        {
                perror("setsockopt: join multicast group with IP_ADD_MEMBERSHIP failed\n");
                exit(1);
        }

        while(1)
        {
                len = recvfrom(sock_channel, recv_buffer, sizeof(recv_buffer), 0, (struct sockaddr*)&remote_addr, &remote_addr_len);
                if(len == -1)
                {
                        perror("%s reception of udp datagramm failed\n");
                        exit(1);
                }
                printf("%s:%d [%d]\t: %s\n", inet_ntoa(remote_addr.sin_addr), ntohs(remote_addr.sin_port), len, recv_buffer);
        }


        return 0;
}



static int emission()
{
        string addresse_ip = "127.0.0.1";

        unsigned char ttl = 1;
        int sock_channel;
        struct sockaddr_in m_socketAddr;
        const char * multicastIPaddr;
        unsigned short port = 55000;
        int len;
        struct sockaddr_in remote_addr;
        socklen_t remote_addr_len = sizeof(struct sockaddr_in);
        unsigned char send_buffer[9000];
        multicastIPaddr = GROUP;
        std::string requete;

        requete = "bonjour";

        // open the socket
        sock_channel = socket(PF_INET, SOCK_DGRAM, 0);
        if(sock_channel < 0)
        {
                perror("Can't open the receive socket, errno %d (%s)\n");
                exit(1);
        }

        // Set destination characteristics to send the datagramms
        // get the remote IP address
        if(inet_aton(GROUP, &(remote_addr.sin_addr))<0)
        {
                perror("cannot get the remote IP address for %s \n");
                exit(1);
        }
        remote_addr.sin_family = AF_INET;
        remote_addr.sin_port = port;

        // initialize the channel
        bzero(&m_socketAddr, sizeof(m_socketAddr));
        m_socketAddr.sin_family = AF_INET;
        m_socketAddr.sin_port = port;
        if(inet_aton(addresse_ip, &(m_socketAddr.sin_addr))<0)
        {
                perror("cannot get the locale IP address for 192.168.18.2 \n");
                exit(1);
        }

        // creation of the link between the socket and its port
        if (bind(sock_channel, (struct sockaddr *)&m_socketAddr,
                sizeof(m_socketAddr)) < 0)
        {
                perror("problem with function bind errno\n");
                exit(1);
        }

        // Activation of the multicast packets sending
        if(setsockopt(sock_channel, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(ttl)) < 0)
        {
                perror("setsockopt: IP_MULTICAST_TTL activation failed\n");
                exit(1);
        }

        len = strlen(requete.c_str()) + 1;
        memcpy(send_buffer, requete.c_str(), len);

        if(sendto(sock_channel, send_buffer, len, 0,
          (struct sockaddr *) &remote_addr, sizeof(remote_addr))< len)
        {
                perror("Error:  sendto(..,0,..) errno %s (%d)\n");
                exit(1);
        }

        return 0;
}

/**Bonjour,

N'y-a-t-il pas un problème de temporisation dans le code posté ?

Le récepteur est il prêt lorsque les données sont envoyées ?

Un simple sleep peut peut-être aider.


Autre chose, je ne suis pas sur de ça :
Code :
Sélectionner tout - Visualiser dans une fenêtre à part

inet_aton("192.168.18.15", &(m_socketAddr.sin_addr));

Pour le réception, j'aurai plutôt mis
Code :
Sélectionner tout - Visualiser dans une fenêtre à part

m_socketAddr.sin_addr = htonl(INADDR_ANY)


Après, on peut auss simplifier le programme

    désactiver le multicast
    mettre serveur et client sur une même machine
    des traces derrière chaque if pour être sur qu'on est pas retenu pas une fonction bloquante.*/
