//
// Created by newbuntu on 09/01/19.
//

#ifndef UNTITLED1_MYTESTCLIENTHANDLER_H
#define UNTITLED1_MYTESTCLIENTHANDLER_H
//
// Created by franckito on 12/18/18.
//
#include <string>
#include "Solver.h"
#include "ClientHandler.h"
#include "CacheManager.h"
using namespace std;
class MyTestClientHandler : public ClientHandler {
public:
    MyTestClientHandler(CacheManager *cm, Solver *solver);

    void handleClient(int sockfd) override;

};




#endif //UNTITLED1_MYTESTCLIENTHANDLER_H
