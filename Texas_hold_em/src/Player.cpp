#include "Player.h"

using namespace std;

Player::Player(string name, string ipAddress)
{
    this->m_name = name;
    this->m_ipAddress = ipAddress;
}

void Player::setMaster(bool master)
{
    this->m_master = master;
}

bool Player::isMaster()
{
    return this->m_master;
}

