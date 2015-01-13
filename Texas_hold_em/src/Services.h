#ifndef SERVICES_H
#define SERVICES_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class Services
{
    public:
        static void* startServer(void* arg);
        static void* sendMessenger(void* arg);
};

#endif // SERVICES_H
