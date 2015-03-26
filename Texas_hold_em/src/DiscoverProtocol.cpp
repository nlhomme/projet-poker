/*******
    Florent Baudon
*******/

#include <vector>
#include <sstream>
#include <string>
#include "DiscoverProtocol.h"
#include "Services.h"
#include "Socket.h"
#include "Multicast.h"

#define HEADPING    "PING"
#define HEADPINGRES "RES"

using namespace std;

vector<Player*> DiscoverProtocol::playerList;
string DiscoverProtocol::myIp = "";

DiscoverProtocol::DiscoverProtocol()
{
    mutex_playerList = PTHREAD_MUTEX_INITIALIZER;
}

DiscoverProtocol::~DiscoverProtocol()
{
    cout << "Destroy" << endl;
    pthread_cancel(threadListener);
    pthread_cancel(threadServerSocket);
    pthread_cancel(threadPing);
}

void DiscoverProtocol::startDiscover()
{

    threadListener = ServicesMulticast::threadListener();
    ServicesMulticast::sendMulticast();
    threadServerSocket = ServicesSocket::thread_server();
    pthread_create(&threadPing,NULL, &DiscoverProtocol::pingPlayers, NULL);
    pthread_create(&threadPingListener, NULL, &DiscoverProtocol::pingResponse, NULL);

    while(true)
    {
        string loginAndAddress = ServicesMulticast::getMessage(); /*recoit le non du joueur et son adresse ip sous le format "192.168.6.6/ipName"*/

        if(!loginAndAddress.empty())
        {
            int indexOfSlash = (int)loginAndAddress.find('/');
            string ipAddress = loginAndAddress.substr(0, indexOfSlash);
            string playerName = loginAndAddress.substr(indexOfSlash+1, loginAndAddress.size()-1);
            cout << "IP : " + ipAddress + "  player : " + playerName << endl;

            //on récupére notre propre ip
            if(playerName==Multicast::getPlayerName())
            {
                DiscoverProtocol::myIp = ipAddress;
            }
            //on verifie si le joeuur est déjà dans le tableau
            bool alreadyInTab = false;
            for(int i=0; i<DiscoverProtocol::playerList.size(); i++)
            {
                pthread_mutex_lock(&mutex_playerList);
                    Player* p = DiscoverProtocol::playerList[i];
                    if(p->getName() == playerName && p->getAddress()==ipAddress)
                    {
                        alreadyInTab = true;
                    }
                pthread_mutex_unlock(&mutex_playerList);
            }

            if(playerName != Multicast::getPlayerName() && !alreadyInTab)
            {
                pthread_mutex_lock(&mutex_playerList);
                    Player* player = new Player(playerName, ipAddress);
                    DiscoverProtocol::playerList.push_back(player);
                pthread_mutex_unlock(&mutex_playerList);

                ServicesMulticast::sendMulticast();

                for(int i=0; i<DiscoverProtocol::playerList.size(); i++)
                {
                    Player* p = DiscoverProtocol::playerList[i];
                    cout << "Name : " << p->getName() << " IP : " << p->getAddress() << " is connected" << endl;
                }
            }
        }
    }
}

void DiscoverProtocol::stopDiscover()
{
    pthread_cancel(threadListener);
    pthread_cancel(threadServerSocket);
}

vector<Player*> DiscoverProtocol::getPlayerList()
{
    return DiscoverProtocol::playerList;
}

void* DiscoverProtocol::pingResponse(void* arg)
{
    while(true)
    {
        sleep(1);
        cout << "response" << endl;
        vector<string>* messagesVector = ServicesSocket::getMessages();

        if(messagesVector->size() > 0){
            //on parcours toute la liste des messages àla recherche d'un message du type PING/[adresseIp]
            for(int i=0; i<messagesVector->size(); i++)
            {
                string m = messagesVector->at(i);
                int indexOfSlash = (int)m.find('/');
                string head = m.substr(0, indexOfSlash);
                string ipAddress = m.substr(indexOfSlash+1, m.size()-1);
                //cout << "HEAD : " << head << "  IP : " << ipAddress << endl;
                if(head == HEADPING)
                {
                    string head = "RES/";
                    string msg = head + Multicast::getLocalAddress();

                    //verifie si le joueur est nouveau, si il l'est on l'ajoute.
                    //Il faudra pensé à ajouter le nom du joueur dans les envoie de ping et tout.
                    bool newPlayer = true;
                    for(int j=0; j< playerList.size(); j++)
                    {
                        Player* player = playerList.at(j);

                        cout << "PONG : " << player->getName() << endl;

                        if(player->getAddress()== ipAddress)
                        {
                            newPlayer = false;
                        }
                    }
                    if(newPlayer)
                    {
                        playerList.push_back(new Player("test", ipAddress));
                    }

                    messagesVector->erase(messagesVector->begin() + i);
                    ServicesSocket::sendAMessage(msg, ipAddress);
                }
            }
        }
    }
}

void* DiscoverProtocol::pingPlayers(void* arg)
{
    while(true)
    {
        //Cool down pour éviter d'envoyer trop de ping à la secondes et surcharger la mémo
        sleep(1);

        if(DiscoverProtocol::playerList.size()>0 )
        {
            for(int i=0; i<DiscoverProtocol::playerList.size(); i++)
            {
                Player* p = DiscoverProtocol::playerList[i];
                cout << "PING : " << p->getName() << endl;

                string head = "PING/";
                string msg = head + Multicast::getLocalAddress();

                ServicesSocket::sendAMessage(msg, p->getAddress());
                /*  envoyer message de type PING/{ip address} où l'adresse ip est celle du programme
                    ensuite lancer un thread avec checkPlayer
                */
                //lance un thread pour checker les players
                pthread_t threadCheckPlayer;
                pthread_create(&threadCheckPlayer,NULL, &DiscoverProtocol::checkPlayer, p);
            }
        }
    }
}

void* DiscoverProtocol::checkPlayer(void* arg)
{
    Player* player = (Player*)arg;
    string ipPlayer = player->getAddress();
    bool playerIsActive = false;
    vector<string>* messagesVector = ServicesSocket::getMessages();

    //on parcours toute la liste des messages àla recherche d'un message du type PING/[adresseIp]
    for(int i=0; i<messagesVector->size(); i++)
    {
        string m = messagesVector->at(i);
        int indexOfSlash = (int)m.find('/');
        string head = m.substr(0, indexOfSlash);
        string ipAddress = m.substr(indexOfSlash+1, m.size()-1);

        if(head == HEADPINGRES)
        {
            if(ipPlayer == ipAddress)
            {
                messagesVector->erase(messagesVector->begin() + i);
                playerIsActive = true;
                cout << "Joueur : " << player->getName() << "toujours là" << endl;
            }
        }
    }

    if(!playerIsActive)
    {
        for(int i=0; i< playerList.size(); i++)
        {
            Player* player = playerList.at(i);

            if(player->getAddress()== ipPlayer)
            {
                playerList.erase(playerList.begin() + i);
            }
        }
    }
}
