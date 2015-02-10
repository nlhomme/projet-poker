#include "Multicast.h"

void Multicast::serverMulti()
{
    int sock;
    IN_ADDR localInterface;
    static SOCKADDR_IN groupSock;
    //décrit le groupe multicast
    ip_mreq gr_multicast;

    //creation du socket UDP
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        perror("Opening datagram error");
        exit(1);
    }

    groupSock.sin_family = AF_INET;
    groupSock.sin_addr.s_addr = inet_addr(GROUP);
    groupSock.sin_port = htons(PORT);

    localInterface.s_addr = inet_addr(LOCALINT);
    if(setsockopt(sock, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localInterface, sizeof(localInterface)) < 0)
    {
        perror("Setting local interface error");
        exit(1);
    }

    char databuf[1024] = "Multicast test message lol!";
    int datalen = sizeof(databuf);

    if(sendto(sock, databuf, datalen, 0, (struct sockaddr*)&groupSock, sizeof(groupSock)) < 0)
    {
        perror("Sending datagram message error");
    }else
    {
        std::cout << "message sent" << std::endl;
    }

}


void Multicast::clientMulti()
{
    std::cout << "Waiting message" << std::endl;
    int sock;
    struct ip_mreq group;
    static SOCKADDR_IN localSock;


    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0)
    {
      perror("Opening datagram socket error");
      exit(1);
    }

    int reuse = 1;
    if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) < 0)
    {
        perror("Setting SO_REUSEADDR error");
        close(sock);
        exit(1);
    }

    localSock.sin_family = AF_INET;
    localSock.sin_port = htons(PORT);
    localSock.sin_addr.s_addr = INADDR_ANY;

     if(bind(sock, (struct sockaddr*)&localSock, sizeof(localSock)))
    {
        perror("Binding datagram socket error");
        close(sock);
        exit(1);
    }
    group.imr_multiaddr.s_addr = inet_addr(GROUP);
    group.imr_interface.s_addr = inet_addr(LOCALINT);

    if(setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&group, sizeof(group)) < 0)
    {
        perror("Adding multicast group error");
        close(sock);
        exit(1);
    }

    char databuf[1024];
    int datalen = sizeof(databuf);

    if(read(sock, databuf, datalen) < 0)
    {
        perror("Reading datagram message error");
        close(sock);
        exit(1);
    }

    std::cout << "message : " << databuf << std::endl;

}
/*
static int reception()
{
        std::string addresse_ip = "127.0.0.1";

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
        if(inet_aton(addresse_ip.c_str(), &(m_socketAddr.sin_addr))<0)
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
        if(inet_aton(addresse_ip.c_str(), (struct in_addr*)&(imr.imr_interface.s_addr))<0)
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
               // printf("%s:%d [%d]\t: %s\n", inet_ntoa(remote_addr.sin_addr), ntohs(remote_addr.sin_port), len, recv_buffer);
               std::cout << recv_buffer << std::endl;
        }


        return 0;
}



static int emission()
{
        std::string addresse_ip = "127.0.0.1";

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
        if(inet_aton(addresse_ip.c_str(), &(m_socketAddr.sin_addr))<0)
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
}*/

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
