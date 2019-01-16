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

class StringReverser : public Solver<string,string> {
    string solve(string entry);

public:
    void * operator new(size_t size)
    {
        void * p = ::new StringReverser();
        //void * p = malloc(size); will also work fine
        Solver *pTag = static_cast<Solver<string, string> *>(p);

        return pTag;
    }

    virtual ~StringReverser();
};
#endif //UNTITLED1_STRINGREVERSER_H
