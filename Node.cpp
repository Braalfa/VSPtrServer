//
// Created by usuario on 25/5/20.
//

#include "Node.h"
#include <iostream>
#include <string>
using namespace std;

using namespace std;

void *Node::getDirMemory()  {
    return dirMemory;

}

void Node::setDirMemory(string value) {

    if(typeid(&this->dirMemory).name()=="int"){
        this->dirMemory= new int(stoi(value)) ;
    }else if (typeid(&this->dirMemory).name() == "double") {
        this->dirMemory= new double(stod(value)) ;
    }else if (typeid(&this->dirMemory).name() == "float") {
        this->dirMemory= new float(stof(value)) ;
    }else if (typeid(&this->dirMemory).name() == "bool") {
        if(value=="true" || value == "1"){
            this->dirMemory= new bool(true);
        }else{
            this->dirMemory= new bool(false);
        }
    }else if (typeid(&this->dirMemory).name() == "string") {
        this->dirMemory= &value;
    }
}

int Node::getReferences() {
    return this->references;
}

string Node::getType(){
    return typeid(this->dirMemory).name();
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
