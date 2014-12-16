#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close (s)

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	int i;
	cin << i << endl;
	if(i==1){
		SOCKET sock;
		SOCKET csock;
		SOCKADDR_IN sin;
		SOCKADDR_IN csin;
		WSAStartup(MAKEWORD(2,0), &WSAData);
		sock = socket(AF_INET, SOCK_STREAM, 0);
		sin.sin_addr.s_addr = INADDR_ANY;
		sin.sin_family = AF_INET;
		sin.sin_port = htons(23);
		bind(sock, (SOCKADDR *)&sin, sizeof(sin));
		listen(sock, 0);
		while(1) /* Boucle infinie. Exercice : améliorez ce code. */
		{
			int sinsize = sizeof(csin);
			if((csock = accept(sock, (SOCKADDR *)&csin, &sinsize)) != INVALID_SOCKET)
			{
				send(csock, "Hello world!\r\n", 14, 0);
				closesocket(csock);
			}
		}
	}else{
		SOCKET sock;
		SOCKADDR_IN sin;
		char buffer[255];
		WSAStartup(MAKEWORD(2,0), &WSAData);
		/* Tout est configuré pour se connecter sur IRC, haarlem, Undernet. */
		sock = socket(AF_INET, SOCK_STREAM, 0);
		sin.sin_addr.s_addr = inet_addr("62.250.14.6");
		sin.sin_family = AF_INET;
		sin.sin_port = htons(6667);
		connect(sock, (SOCKADDR *)&sin, sizeof(sin));
		recv(sock, buffer, sizeof(buffer), 0);
		closesocket(sock);
		WSACleanup();
		return 0;	
	}
	
    return 0;
}

