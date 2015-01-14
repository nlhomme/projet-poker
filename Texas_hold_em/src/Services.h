#ifndef SERVICES_H
#define SERVICES_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <pthread.h>

class Services
{
    public :
        static pthread_t* thread_server();
        static pthread_t* thread_messenger();
    private :
        static void* startServer(void* arg);
        static void* sendMessenger(void* arg);
};

#endif // SERVICES_H
