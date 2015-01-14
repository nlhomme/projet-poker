#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <pthread.h>

#include "Services.h"

using namespace std;

int main(int argc, char *argv[])
{
    Services::thread_server();
    Services::thread_messenger();

    while(true){
        string msg = Services::getMessage();
        if(!msg.empty())
        {
            cout << msg << endl;
        }
    }
}
