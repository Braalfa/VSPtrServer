//
// Created by usuario on 25/5/20.
//

#ifndef VSCODEMEMORY_NODE_H
#define VSCODEMEMORY_NODE_H

using namespace std;
#include "string"

class Node {
private:
    void* dirMemory ;
    int references;
    int ID;
    string type;

public:
    static int generateID();

    Node *next;
    Node();
    Node(void *dirMemory, string type);

    void *getDirMemory();
    void setDirMemory(void *dirMemory);

    int getID();
    int getReferences();

    void deleteReferences();
    void addReferences();

    void setType(string type);
    string getType();

};

#endif //VSCODEMEMORY_NODE_H
