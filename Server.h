//
// Created by newbuntu on 08/01/19.
//
#ifndef UNTITLED1_SERVER_H
#define UNTITLED1_SERVER_H
#include "ClientHandler.h"

namespace server_side {
    class Server {
    public:
        // pure virtual function
        virtual void open(int port, ClientHandler *c) = 0;

        virtual void stop() = 0;
    };
}

#endif //UNTITLED1_SERVER_H
