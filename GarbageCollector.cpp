//
// Created by usuario on 22/5/20.
//
#include <thread>
#include <chrono>
#include "GarbageCollector.h"

GarbageCollector* GarbageCollector::instance = 0;

GarbageCollector::GarbageCollector(){
    threadRun();
}



GarbageCollector* GarbageCollector::getInstance()
{
    if (instance == 0)
    {
        instance = new GarbageCollector();
    }
    return instance;
}


void GarbageCollector::threadRun() {
    this_thread::sleep_for (chrono::seconds(1/2));
    while (true){
        Node *present = getList()->getFirst();
        while (present != nullptr){
            if(present->getReferences() == 0){
                GarbageCollector::getList()->deleteNode(present->getID());
            }
            present = present->next;
        }
        present = getList()->getFirst();
    }
}

List * GarbageCollector::getList() {
    return this->listGarbageCollector;
}

void GarbageCollector::deleteReferences(int ID){
    getList()->deleteReferences(ID);
}
int GarbageCollector::addNode(void* ptr){
    return getList()->addNode(ptr);
}
void GarbageCollector::addReferences(int ID){
    getList()->addReferences(ID);
}
void GarbageCollector::setMemory(string value, int ID){
    getList()->getNode(ID).setDirMemory(value);
}
string GarbageCollector::getType(int ID){
    return getList()->getNode(ID).getType();
}
