#include "server.h"
#include "hl_md5.h"
#include "hl_md5wrapper.h"
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include "json.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>    //close
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include <fstream>
#include "GarbageCollector.h"
#define TRUE   1
#define PORT 8888
#define ADDRESS "127.0.0.1"

Server::Server()
{
    password="myproyectpassword";
    password=getmd5(password);
}



Json::Value Server::toJson(string message){
    Json::Value val;
    Json::Reader reader;
    bool b = reader.parse(message, val);
    if (!b)
        cout << "Error: " << reader.getFormattedErrorMessages();
    return val;
}

void Server::sendConnection(int socket, std::string username, std::string pass){
    Json::Value root;
    root["socket"] = socket;
    root["ip"] = ADDRESS;
    root["port"] = PORT;
    root["username"] = username;
    root["password"] = pass;

    Json::FastWriter fastwriter;
    std::string document = fastwriter.write(root);

    char message[document.size() + 1];
    strcpy(message, document.c_str());
    send(socket, message, strlen(message),0);
}


void Server::sendMsg(int socket,string msg){
    char message[msg.size() + 1];
    strcpy(message,msg.c_str());
    send(socket, message, strlen(message),0);
}

void Server::manageLogin( int sd, string message, string *userName) {
    string line;
    ifstream MyReadFile("users.txt");

    int pos = message.find_first_of(";");
    string clientUser = message.substr(0, pos);
    message.erase(0, pos + 1);
    pos = message.find_first_of(";");
    string clientPassword = message.substr(0, pos);

    string user;

    if (password == clientPassword) {
        bool userFound = false;
        while (getline(MyReadFile, line)) {
            pos = line.find_first_of(";");
            user = line.substr(0, pos);

            if (user == clientUser) {
                userFound = true;
                *userName = user;
                sendConnection(sd, user, password);
                break;
            }
        }
        MyReadFile.close();
        if (!userFound) {
            std::ofstream outfile;
            outfile.open("users.txt", std::ios_base::app);
            outfile << clientUser+";";
            *userName = clientUser;
        }
    } else {
        send(sd, "connection failed",17,0);
    }

}

void Server::manageCalls(int sd, char buffer[1024], string *user) {
    string message;
    string command;
    int pos;
    message = buffer;
    pos = message.find_first_of(";");
    command = message.substr(0, pos);
    message.erase(0, pos + 1);


    if (command == "log-in") {
        manageLogin(sd, message, user);
    } else if (!user->empty()) {

        if (command == "new-vs") {
            pos = message.find_first_of(";");
            string json = message.substr(0, pos);
            message.erase(0, pos + 1);

            Json::Value data = toJson(json);
            Json::Value typeVal=data["type"];
            Json::Value dataVal=data["data"];

            void *ptr= nullptr;
            int id=GarbageCollector::getInstance()->addNode(ptr, typeVal.asString());

            sendMsg(sd, to_string(id));

        }else{

            pos = message.find_first_of(";");
            int id = std::stoi(message.substr(0, pos));
            message.erase(0, pos + 1);

            if (command == "new-ref") {
                GarbageCollector::getInstance()->addReferences(id);
            }else if (command == "delete-ref") {
                int references = GarbageCollector::getInstance()->getList()->getNode(id)->getReferences()-1;
                GarbageCollector::getInstance()->deleteReferences(id);
                sendMsg(sd, to_string(references==0));
            }else if(command == "update"){

                pos = message.find_first_of(";");
                string json = message.substr(0, pos);
                message.erase(0, pos + 1);

                Json::Value data = toJson(json);
                Json::Value typeVal=data["type"];
                Json::Value dataVal=data["data"];

                void *ptr = nullptr;
                if(typeVal.asString()=="string"){
                    ptr = new string(dataVal.asString());
                }else if(typeVal.asString()=="b"){
                    ptr = new bool(dataVal.asString() == "true");
                }else if(typeVal.asString()=="d"){
                    ptr = new double(stod(dataVal.asString()));
                }else if(typeVal.asString()=="i"){
                    ptr = new int(stoi(dataVal.asString()));
                }else if(typeVal.asString()=="f"){
                    ptr = new float(stof(dataVal.asString()));
                }
                GarbageCollector::getInstance()->setMemory(ptr,id,typeVal.asString());

                std::ostringstream addressh;
                addressh<< ptr;
                string address = addressh.str();

                sendMsg(sd, address);
            }
        }
    }

}

string Server::getmd5(string pass){
    md5wrapper md5=md5wrapper();
    pass=md5.getHashFromString(pass);
    return pass;
}

int Server::run() {

    int opt = TRUE;
    int master_socket, addrlen, new_socket, client_socket[30],
            max_clients = 30, activity, i, valread, sd;
    string user[30];
    int max_sd;
    string msg;
    char *message =  const_cast<char*>(msg. c_str());;
    struct sockaddr_in address;

    char buffer[1025];  //data buffer of 1K
    //set of socket descriptors
    fd_set readfds;
    //a message
    //initialise all client_socket[] to 0 so not checked
    for (i = 0; i < max_clients; i++) {
        client_socket[i] = 0;
    }

    //create a master socket
    if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    //set master socket to allow multiple connections ,
    //this is just a good habit, it will work without this
    if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *) &opt,
                   sizeof(opt)) < 0) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    //type of socket created
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ADDRESS);;
    address.sin_port = htons(PORT);

    //bind the socket to localhost port 8888
    if (bind(master_socket, (struct sockaddr *) &address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Listener on port %d \n", PORT);

    //try to specify maximum of 3 pending connections for the master socket
    if (listen(master_socket, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    //accept the incoming connection
    addrlen = sizeof(address);
    puts("Waiting for connections ...");

    while (TRUE) {
        //clear the socket set
        FD_ZERO(&readfds);

        //add master socket to set
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;



        //add child sockets to set
        for (i = 0; i < max_clients; i++) {
            //socket descriptor
            sd = client_socket[i];

            //if valid socket descriptor then add to read list
            if (sd > 0)
                FD_SET(sd, &readfds);

            //highest file descriptor number, need it for the select function
            if (sd > max_sd)
                max_sd = sd;
        }

        //wait for an activity on one of the sockets , timeout is NULL ,
        //so wait indefinitely
        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

        if ((activity < 0) && (errno != EINTR)) {
            printf("select error");
        }

        //If something happened on the master socket ,
        //then its an incoming connection
        if (FD_ISSET(master_socket, &readfds)) {
            new_socket = accept(master_socket,
                                (struct sockaddr *) &address, (socklen_t *) &addrlen);
            if (new_socket < 0) {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            //inform user of socket number - used in send and receive commands
            printf("New connection , socket fd is %d , ip is : %s , port : %d\n", new_socket,
                   inet_ntoa(address.sin_addr), ntohs
                           (address.sin_port));

            //send new connection greeting message
            if (send(new_socket, &"greetings, socket number: "[new_socket], strlen(message), 0) != strlen(message)) {
                perror("send");
            }

            puts("Welcome message sent successfully");

            //add new socket to array of sockets
            for (i = 0; i < max_clients; i++) {
                //if position is empty
                if (client_socket[i] == 0) {
                    client_socket[i] = new_socket;
                    printf("Adding to list of sockets as %d\n", i);

                    break;
                }
            }
        }

        //else its some IO operation on some other socket
        for (i = 0; i < max_clients; i++) {
            sd = client_socket[i];

            if (FD_ISSET(sd, &readfds)) {
                //Check if it was for closing , and also read the
                //incoming message
                if ((valread = read(sd, buffer, 1024)) == 0) {
                    //Somebody disconnected , get his details and print
                    getpeername(sd, (struct sockaddr *) &address, \
                        (socklen_t *) &addrlen);
                    printf("Host disconnected , ip %s , port %d \n",
                           inet_ntoa(address.sin_addr), ntohs(address.sin_port));

                    //Close the socket and mark as 0 in list for reuse
                    close(sd);
                    client_socket[i] = 0;
                }
                    //Echo back the message that came in
                else {
                    manageCalls(sd, buffer, &user[i]);
                }
            }
        }
    }
}
