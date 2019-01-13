//
// Created by newbuntu on 09/01/19.
//

#ifndef UNTITLED1_STRINGREVERSER_H
#define UNTITLED1_STRINGREVERSER_H

#include <string>
#include "Solver.h"
#include "ClientHandler.h"
#include "CacheManager.h"

using namespace std;

class StringReverser : public Solver {
    string solve(string entry);
};
#endif //UNTITLED1_STRINGREVERSER_H
