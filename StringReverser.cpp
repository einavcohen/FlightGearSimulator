//
// Created by newbuntu on 09/01/19.
//

#include <string>
#include "Solver.h"
#include "ClientHandler.h"
#include "CacheManager.h"
#include "StringReverser.h"

using namespace std;

string StringReverser::solve(string entry) {
    char ret[entry.length()];
    int i = 0;
    for(char& c : entry){
        ret[i] = c;
        i++;
    }
    return string(ret);
}

StringReverser::~StringReverser() {}
