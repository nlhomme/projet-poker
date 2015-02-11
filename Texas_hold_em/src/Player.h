#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

class Player
{
    public:
        Player(std::string name, std::string ipAddress);
        void setMaster(bool master);
        bool isMaster();
    private :
        std::string m_name;
        std::string m_ipAddress;
        bool m_master;
};

#endif // PLAYER_H
