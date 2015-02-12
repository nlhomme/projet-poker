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
        static void* checkPlayer(void* arg);

        pthread_t threadListener;
        pthread_t threadServerSocket;
        pthread_mutex_t mutex_playerList;
        static std::vector<Player*> playerList;
};

#endif // DISCOVERPROTOCOL_H
