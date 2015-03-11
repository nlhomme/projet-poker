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
vector<string>* ServicesSocket::messagesVector = new vector<string>;

/*Lance un listener*/
void* ServicesSocket::startServer(void* arg)
{
    cout << "Socket server start" << endl;
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

vector<string>* ServicesSocket::getMessages()
{
    return ServicesSocket::messagesVector;
}

void ServicesSocket::addMessage(string msg)
{
    ServicesSocket::messagesVector->push_back(msg);
}

void ServicesSocket::setHostname(string hostname)
{
    ServicesSocket::hostname = hostname;
}

void ServicesSocket::sendAMessage(string msg, string hostname)
{
    if(!msg.empty())
    {
        Socket::clientSocket(msg, hostname);
    }
}
/************************************************************************************************************************************/
//MULTICAST
/************************************************************************************************************************************/

string ServicesMulticast::message ="";
pthread_mutex_t ServicesMulticast::message_mutex = PTHREAD_MUTEX_INITIALIZER;

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
        string message = Multicast::clientMulti();

        if(!message.empty())
        {
            //cout << message << endl;
            //Verouillage des message par un mutex pour par editer la variable en même temps que le getMessage
            pthread_mutex_lock(&ServicesMulticast::message_mutex);
                ServicesMulticast::message = message;
            pthread_mutex_unlock(&ServicesMulticast::message_mutex);            // dévérouillage du mutex

        }
    }
}

void ServicesMulticast::multicastMessenger(string message)
{
    Multicast::messenger(message);
}

string ServicesMulticast::getMessage()
{
    //Verouillage des message par un mutex pour par editer la variable en même temps que le listener
    pthread_mutex_lock(&ServicesMulticast::message_mutex);
        string message = ServicesMulticast::message;
        ServicesMulticast::message = "";
    pthread_mutex_unlock(&ServicesMulticast::message_mutex);    // dévérouillage du mutex

    return message;
}


