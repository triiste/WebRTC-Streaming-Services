#include<iostream>

#include "server.h"

int main()
{
    avdance::Server *server = new avdance::Server();
    if(server){
        server->run();
    }
    return 0;
}
