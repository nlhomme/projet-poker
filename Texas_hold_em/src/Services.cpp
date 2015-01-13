#include "Services.h"
#include "Socket.h"

using namespace std;

/*Class contenant tout les services utilisant les we socket*/

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


