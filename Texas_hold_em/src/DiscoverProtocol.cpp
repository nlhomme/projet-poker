/*******
    Florent Baudon
*******/

#include "DiscoverProtocol.h"
#include "Services.h"
#include "Socket.h"
#include "Multicast.h"

using namespace std;

vector<Player*> DiscoverProtocol::playerList;

DiscoverProtocol::DiscoverProtocol()
{
    mutex_playerList = PTHREAD_MUTEX_INITIALIZER;
}

DiscoverProtocol::~DiscoverProtocol()
{
    cout << "Destroy" << endl;
    pthread_cancel(threadListener);
    pthread_cancel(threadServerSocket);
}

void DiscoverProtocol::startDiscover()
{
    ServicesMulticast::sendMulticast();
    threadListener = ServicesMulticast::threadListener();
    threadServerSocket = ServicesSocket::thread_server();

    pthread_t thread;
    //pthread_create(&thread,NULL, &DiscoverProtocol::checkPlayer, NULL);


    while(true)
    {
        string loginAndAddress = ServicesMulticast::getMessage(); /*recoit le non du joueur et son adresse ip sous le format "192.168.6.6/ipName"*/

        if(!loginAndAddress.empty())
        {
            int indexOfSlash = (int)loginAndAddress.find('/');
            string ipAddress = loginAndAddress.substr(0, indexOfSlash-1);
            string playerName = loginAndAddress.substr(indexOfSlash+1, loginAndAddress.size()-1);

            //on verifie si le joeuur est déjà dans le tableau
            bool alreadyInTab = false;
            for(int i=0; i<DiscoverProtocol::playerList.size(); i++)
            {
                cout << "test 1" << endl;
                pthread_mutex_lock(&mutex_playerList);
                    Player* p = DiscoverProtocol::playerList[i];
                    if(p->getName() == playerName && p->getAddress()==ipAddress)
                    {
                        cout << "test 2" << endl;
                        alreadyInTab = true;
                    }
                pthread_mutex_lock(&mutex_playerList);
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

void* DiscoverProtocol::checkPlayer(void* arg)
{
    while(true)
    {
        if(DiscoverProtocol::playerList.size()>0)
        {
            for(int i=0; i<DiscoverProtocol::playerList.size(); i++)
            {
                Player* p = DiscoverProtocol::playerList[i];
                Socket::clientSocket("PING", p->getAddress());
                int r = 0;
                r = Socket::serverSocket();

                if(r==0)
                {
                    DiscoverProtocol::playerList.erase(DiscoverProtocol::playerList.begin()+i);
                }
            }
        }
    }
}
