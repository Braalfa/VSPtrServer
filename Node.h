//
// Created by usuario on 25/5/20.
//

#ifndef VSCODEMEMORY_NODE_H
#define VSCODEMEMORY_NODE_H

#include <string>
#include <iostream>
using namespace std;

class Node {
private:
    void* dirMemory ;
    int references;
    int ID;

public:
    static int generateID();

    Node *next;
    Node();
    Node(void *dirMemory);

    void *getDirMemory();
    void setDirMemory(string value);

    int getID();
    int getReferences();

    void deleteReferences();
    void addReferences();

    string getType();

};

#endif //VSCODEMEMORY_NODE_H
