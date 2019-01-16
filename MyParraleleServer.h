//
// Created by newbuntu on 15/01/19.
//

#ifndef UNTITLED1_MYPARRALELESERVER_H
#define UNTITLED1_MYPARRALELESERVER_H
#include "Server.h"
using namespace server_side;
using namespace std;

class MyParraleleServer : public server_side::Server{
public:
    int sock_fd;

    MyParraleleServer();

    void start(int sockfd, ClientHandler *ch);

    void stop() override;

    void open(int port, ClientHandler *c) override;

    static void *socketThread(void *arg);
};



#endif //UNTITLED1_MYPARRALELESERVER_H
