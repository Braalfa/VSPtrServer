//
// Created by usuario on 25/5/20.
//

#include "Node.h"

void *Node::getDirMemory()  {
    return dirMemory;
}

void Node::setDirMemory(void *dirMemory) {
    this->dirMemory = dirMemory;
}

int Node::getReferences() {
    return this->references;
}

void Node::deleteReferences() {
    this->references = references-1;
}

void Node::addReferences() {
    this->references = references+1;

}

Node::Node() {
    next = nullptr;
}

Node::Node(void *dirMemory) {
    next = nullptr;
    this->dirMemory = dirMemory;
    this->ID = generateID();
    this->references = 1;
}

int Node::generateID() {
    static int i;
    return ++i;
}

int Node::getID() {
    return this->ID;
}
