//
// Created by newbuntu on 09/01/19.
//

#ifndef UNTITLED1_MYTESTCLIENTHANDLER_H
#define UNTITLED1_MYTESTCLIENTHANDLER_H
//
// Created by franckito on 12/18/18.
//
#define DELIMITER '$'
#define CACHE_FILE "cachefile.txt"
#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include "Solver.h"
#include "ClientHandler.h"
#include "CacheManager.h"
#include "CacheManager.h"
#include <mutex>
using namespace std;

template class CacheManager<string, string>;

class MyTestClientHandler : public ClientHandler {
    CacheManager<string, string> *cm;
    Solver<string, string> *solver;
public:
    MyTestClientHandler(CacheManager<string, string> *cm, Solver<string, string> *solver);

    CacheManager<string, string> *getCm() const;

    Solver<string, string> *getSolver() const;

    void handleClient(int sockfd) override;

};


#endif //UNTITLED1_MYTESTCLIENTHANDLER_H
