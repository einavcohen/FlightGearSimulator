//
// Created by newbuntu on 09/01/19.
//

#ifndef UNTITLED1_MYSERIALSERVER_H
#define UNTITLED1_MYSERIALSERVER_H
#include "Server.h"
using namespace server_side;
using namespace std;

class MySerialServer : public server_side::Server{
public:
    int sock_fd;

    MySerialServer();

    void start(int sockfd, ClientHandler *ch);

    void stop() override;

    void open(int port, ClientHandler *c) override;
};


#endif //UNTITLED1_MYSERIALSERVER_H