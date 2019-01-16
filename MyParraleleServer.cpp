//
// Created by newbuntu on 15/01/19.
//

#include "MyParraleleServer.h"
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <wait.h>
#include<pthread.h>

struct arg_struct {
    int socket;
    ClientHandler *ch;
};

char client_message[2000];

char buffer[1024];

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

MyParraleleServer::MyParraleleServer() = default;

arg_struct *init_Data(int s, ClientHandler *ch){
arg_struct *arg = new arg_struct();
arg->ch = ch;
arg->socket = s;
return arg;
}

void *MyParraleleServer::socketThread(void *args)

{

    arg_struct newArg = *((arg_struct *)args);
    recv(newArg.socket , client_message , 2000 , 0);
    pthread_mutex_lock(&lock);
    char* message = static_cast<char *>(malloc(sizeof(client_message) + 20));
    strcpy(message,"Hello Client : ");
    strcat(message,client_message);
    strcat(message,"\n");
    strcpy(buffer,message);
    free(message);
    newArg.ch->handleClient(newArg.socket);
    pthread_mutex_unlock(&lock);
    sleep(1);
    printf("Exit socketThread \n");
    close(newArg.socket);
    pthread_exit(NULL);

}



void MyParraleleServer::start(int serverSocket, ClientHandler *ch) {
    int newSocket;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;

    if(listen(serverSocket,50)==0)
        printf("Listening\n");

    else
        printf("Error\n");

    pthread_t tid[50];

    int i = 0;

    while(1) {
        addr_size = sizeof serverStorage; //Accept call creates a new socket for the incoming connection
        newSocket = accept(serverSocket, (struct sockaddr *) &serverStorage, &addr_size); //for each client request creates a thread and assign the client request to it to process
        if( pthread_create(&tid[i], NULL, &MyParraleleServer::socketThread, init_Data(newSocket, ch)) != 0 ) { // so the main thread can entertain next request
            printf("Failed to create thread\n");
            break;
        }

        if( i >= 50)
        {
            i = 0;
            while(i < 50)
            {
                pthread_join(tid[i++],NULL);
            }
            i = 0;
        }
    }
}


void MyParraleleServer::stop() {
        close(sock_fd);
}


void MyParraleleServer::open(int port, ClientHandler *c) {
    int serverSocket;
    struct sockaddr_in serverAddr;

    //Create the socket.

    serverSocket = socket(PF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    start(serverSocket,c);

}
