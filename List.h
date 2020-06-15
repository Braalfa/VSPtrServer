//
// Created by Juan Solis on 25/5/20.
//

#ifndef VSCODEMEMORY_LIST_H
#define VSCODEMEMORY_LIST_H

#include "Node.h"

/**
 * La lista se encarga de almacenar la informacion de las direcciones de memoria para el Garbage
 * Collector
 */
class List {
    Node *first;
public:
    Node *getFirst();
    List();

    void setMemory(void *dirMemory, int ID);
    void deleteNode(int ID);
    Node* getNode(int ID);

    void deleteReferences(int ID);
    void addReferences(int ID);

    void updateValue(void* newValue);
    void printList();

    int addNode(void *dirMemory, string type);
};


#endif //VSCODEMEMORY_LIST_H
