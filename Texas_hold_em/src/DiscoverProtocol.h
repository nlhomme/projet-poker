/*******
    Florent Baudon
*******/

#ifndef DISCOVERPROTOCOL_H
#define DISCOVERPROTOCOL_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <pthread.h>
#include <vector>
#include "Player.h"


class DiscoverProtocol
{
    public:
        DiscoverProtocol();
        virtual ~DiscoverProtocol();
        void startDiscover();
        void stopDiscover();
        std::vector<Player*> getPlayerList();
    protected:
    private:
        static std::string myIp;
        //ping les jouerus pour v�rifier leurs connections
        static void* pingPlayers(void* arg);
        //verirfie si le joueur � r�pondu au ping et le supprime si pas de r�ponse
        static void* checkPlayer(void* ip);
        //r�pond au ping
        static void* pingResponse(void *arg);

        pthread_t threadListener;
        pthread_t threadServerSocket;
        pthread_t threadPing;
        pthread_mutex_t mutex_playerList;
        static std::vector<Player*> playerList;
};

#endif // DISCOVERPROTOCOL_H
