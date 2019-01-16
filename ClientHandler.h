//
// Created by newbuntu on 08/01/19.
//

#ifndef UNTITLED1_CLIENTHANDLER_H
#define UNTITLED1_CLIENTHANDLER_H

#include "CacheManager.h"
#include "Solver.h"
#include "iostream"
using namespace std;

class ClientHandler {
public:
    virtual void handleClient(int sockfd) = 0;
};

#endif //UNTITLED1_CLIENTHANDLER_H
