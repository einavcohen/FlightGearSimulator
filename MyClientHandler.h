//
// Created by newbuntu on 14/01/19.
//

#ifndef UNTITLED1_MYCLIENTHANDLER_H
#define UNTITLED1_MYCLIENTHANDLER_H


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
#include "Searchable.h"
#include <mutex>
using namespace std;

template class CacheManager<string, string>;

class MyClientHandler : public ClientHandler {
    CacheManager<string, string> *cm;
    Solver<Searchable *, SearchResult> *solver;
public:


    CacheManager<string, string> *getCm() const;

    MyClientHandler(CacheManager<string, string> *cm, Solver<Searchable *, SearchResult> *solver);

    Solver<Searchable *, SearchResult> *getSolver() const;

    void handleClient(int sockfd) override;

    template <class T>
    static vector<T> append(vector<T> a, vector<T> b);

    template <class T>
    string vecToString(vector<T> vec);


};


#endif //UNTITLED1_MYCLIENTHANDLER_H
