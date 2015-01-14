#include "Services.h"
#include "Socket.h"

using namespace std;

/*Class contenant tout les services utilisant les we socket*/

/*initialisation de la variable statique*/
string Services::message = "";

/*Lance un listener*/
void* Services::startServer(void* arg)
{
    Socket::serverSocket();
}

/*lance une messagerie instannée*/
void* Services::sendMessenger(void* arg)
{
    /*Demande du hostname du receveur*/
    cout << "Hostname :" << endl;
    string hostname;
    getline(cin,hostname);

    bool exit = false;

    while(!exit){
        /*demande du message*/
        cout << "message :";
        string msg;
        getline(cin,msg);

        if(!msg.compare("exit"))
        {
            Socket::clientSocket("Client à quitté la conversation", hostname);
            cout << "Arrêt de la conversation" << endl;
            exit = true;
        }else
        {
            Socket::clientSocket(msg, hostname);
        }
    }
}

pthread_t Services::thread_server()
{
    /*créer les thread serveur*/
    pthread_t server_thread;

    /*lance les threads*/
    pthread_create(&server_thread, NULL, &Services::startServer, NULL);

    return server_thread;
}

pthread_t Services::thread_messenger()
{
        /*créer les thread serveur*/
    pthread_t messenger_thread;

    /*lance les threads*/
    pthread_create(&messenger_thread, NULL, &Services::sendMessenger, NULL);

    return messenger_thread;
}

void Services::receivedMessage(string msg)
{
    Services::message = msg;
}

string Services::getMessage()
{
    if(!Services::message.empty())
    {
        string returnMsg = Services::message;
        Services::message = "";
        return returnMsg;
    }else
    {
        return "";
    }
}
