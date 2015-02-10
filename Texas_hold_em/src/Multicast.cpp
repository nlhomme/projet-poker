/*******
    Florent Baudon
*******/

#include "Multicast.h"

void Multicast::serverMulti()
{
    const std::string localInt = getLocalAddress();

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

    localInterface.s_addr = inet_addr(localInt.c_str());
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
    const std::string localInt = getLocalAddress();

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
    group.imr_interface.s_addr = inet_addr(localInt.c_str());

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

std::string Multicast::getLocalAddress()
{
    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;

    getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (ifa ->ifa_addr->sa_family==AF_INET)
        { // check it is IP4
            // is a valid IP4 Address
            tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            //printf("'%s': %s\n", ifa->ifa_name, addressBuffer);
            if(strcmp(addressBuffer, "127.0.0.1"))
            {
                std::string localAdress = (std::string)addressBuffer;
                return localAdress;
            }

         } /*else if (ifa->ifa_addr->sa_family==AF_INET6)
         { // check it is IP6
            // is a valid IP6 Address
            tmpAddrPtr=&((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr;
            char addressBuffer[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
            //printf("'%s': %s\n", ifa->ifa_name, addressBuffer);
        }*/
    }
    if (ifAddrStruct!=NULL)
        freeifaddrs(ifAddrStruct);//remember to free ifAddrStruct
    return 0;
}
