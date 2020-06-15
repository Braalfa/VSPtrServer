#ifndef SERVER_H
#define SERVER_H


#include <string>

using namespace std;

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include "json.h"
#include <stdio.h>
#include <string.h>   //strlen
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>    //close
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include "GarbageCollector.h"
#define TRUE   1
#define PORT 8888
#define ADDRESS "127.0.0.1"

/**
 * Clase Server para manejar las solicitudes del cliente
 */
class Server
{
private:
    Json::Value toJson(string message);
    string getmd5(string pass);
    string password;
public:
    void sendConnection(int socket, std::string username, std::string pass);
    void manageLogin( int sd, string message, string *userName);
    void manageCalls(int sd, char buffer[1024], string *user);
    int run();
    void sendMsg(int socket,string msg);
    Server();

};

#endif // SERVER_H
