#include <iostream>
#include <fstream>
#include <string>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

/*************************************************************************************
* Function name: main
* Input: none
* Output: none
* Function Operation: Gets as argument a string which is a location of a script to run.
**************************************************************************************/
#include "MySerialServer.h"
#include "Server.h"
#include "MyClientHandler.h"
#include "StringReverser.h"
#include "FileCacheManager.h"
#include "ClientHandler.h"
#include "SearcherSolver.h"
#include "BFS.h"
#include "DFS.h"
#include <string>
using namespace server_side;

    int main(int argc, char **argv) {
        BFS *new_bfs = new BFS();
        Server* s = new MySerialServer();
        s->open(atoi(argv[1]), new MyClientHandler(new FileCacheManager(), new (new_bfs) SearcherSolver(new_bfs)));
        return 0;
    }