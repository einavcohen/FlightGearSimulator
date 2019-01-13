//
// Created by newbuntu on 09/01/19.
//
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <streambuf>
#include "CacheManager.h"
#include "MyTestClientHandler.h"


void MyTestClientHandler::handleClient(int sockfd) {
char bufferIn[1026];
CacheManager *ch = getCm();
int n;
string resp;
bool end = false;
while(!end) {
    bzero(bufferIn, 1025);
    n = (int) read(sockfd, bufferIn, 1025);
    if (n < 0) {
        perror("ERROR reading from socket");
        pthread_exit(NULL);
    }
    if (strcmp(bufferIn, "end")) {
        end = true;
        break;
    }
    if (ch->keyExistInCache(bufferIn)) {
        resp = ch->loadFromCache(string(bufferIn));
        /* Write a response to the client */
    } else {
        Solver *s = getSolver();
        resp = s->solve(bufferIn);
        ch->saveDataInCache(bufferIn, resp);
    }
    n = send(sockfd, resp.c_str(), strlen(resp.c_str()), 0);

    if (n < 0) {
        perror("ERROR writing to socket");
        exit(1);
    }
}
}

MyTestClientHandler::MyTestClientHandler(CacheManager *cm, Solver *solver) : ClientHandler(cm, solver) {}
