/*******
    Florent Baudon
*******/
#include "Services.h"
#include "Socket.h"
#include "Multicast.h"

using namespace std;


/************************************************************************************************************************************/
//SOCKET
/************************************************************************************************************************************/

/*initialisation de la variable statique*/
string ServicesSocket::message = "";
string ServicesSocket::hostname = "";

/*Lance un listener*/
void* ServicesSocket::startServer(void* arg)
{
    Socket::serverSocket();
}

/*lance une messagerie instannée*/
void* ServicesSocket::sendMessenger(void* arg)
{
    bool exit = false;

    while(!exit){
        /*demande du message*/
        cout << "message :";
        string msg;
        getline(cin,msg);

        if(!msg.compare("exit"))
        {
            Socket::clientSocket("Client à quitté la conversation", ServicesSocket::hostname);
            cout << "Arrêt de la conversation" << endl;
            exit = true;
        }else
        {
            Socket::clientSocket(msg, ServicesSocket::hostname);
        }
    }
}

pthread_t ServicesSocket::thread_server()
{
    /*créer les thread serveur*/
    pthread_t server_thread;

    /*lance les threads*/
    pthread_create(&server_thread, NULL, &ServicesSocket::startServer, NULL);

    return server_thread;
}

pthread_t ServicesSocket::thread_messenger()
{
        /*créer les thread serveur*/
    pthread_t messenger_thread;

    /*lance les threads*/
    pthread_create(&messenger_thread, NULL, &ServicesSocket::sendMessenger, NULL);

    return messenger_thread;
}

void ServicesSocket::receivedMessage(string msg)
{
    ServicesSocket::message = msg;
}

string ServicesSocket::getMessage()
{
    if(!ServicesSocket::message.empty())
    {
        string returnMsg = ServicesSocket::message;
        ServicesSocket::message = "";
        return returnMsg;
    }else
    {
        return "";
    }
}

void ServicesSocket::setHostname(string hostname)
{
    ServicesSocket::hostname = hostname;
}

void ServicesSocket::sendAMessage(string msg)
{
    if(!msg.empty())
    {
        Socket::clientSocket(msg, ServicesSocket::hostname);
    }
}
/************************************************************************************************************************************/
//MULTICAST
/************************************************************************************************************************************/
void ServicesMulticast::setPlayerName(std::string name)
{
    Multicast::setPlayerName(name);
}

pthread_t ServicesMulticast::threadListener()
{
    /*créer les thread slistner*/
    pthread_t listener_thread;

    /*lance les threads*/
    pthread_create(&listener_thread, NULL, &ServicesMulticast::startListener, NULL);

    return listener_thread;
}
void ServicesMulticast::sendMulticast()
{
    Multicast::serverMulti();
}

void* ServicesMulticast::startListener(void* arg)
{
    while(true)
    {
        Multicast::clientMulti();
    }
}
