//
// Created by einav on 08/01/19.
//

#ifndef MILESTONE_2_CLIENTHANDLER_H
#define MILESTONE_2_CLIENTHANDLER_H


using namespace std;

class ClientHandler {
public:
    template <class T>
    void handleClient(T inputStream,T outputStream);
};

#endif //MILESTONE_2_CLIENTHANDLER_H
