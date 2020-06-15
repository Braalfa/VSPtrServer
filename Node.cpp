//
// Created by usuario on 25/5/20.
//

#include "Node.h"
#include "string"
#include "iostream"

using namespace std;
void *Node::getDirMemory()  {
    return dirMemory;
}

void Node::setDirMemory(void *dirMemory) {
    this->dirMemory = dirMemory;
    cout<<this->dirMemory<<endl;
    cout<<this->ID<<endl;

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

Node::Node(void *dirMemory, string type) {
    next = nullptr;
    this->dirMemory = dirMemory;
    this->ID = generateID();
    this->references = 1;
    this->type= type;
}

int Node::generateID() {
    static int i;
    i = i+1;
    int y= i;
    return y;
}

int Node::getID() {
    return this->ID;
}

void Node::setType(string type){
    this->type= type;
}
string Node::getType(){
    return this->type;
}