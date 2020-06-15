//
// Created by usuario on 22/5/20.
//

#include <sstream>
#include <chrono>
#include <thread>
#include "GarbageCollector.h"
#include "iostream"

GarbageCollector* GarbageCollector::instance = 0;
std::mutex GarbageCollector::mutex ;

GarbageCollector::GarbageCollector(){
    listGarbageCollector= new List;
}


GarbageCollector* GarbageCollector::getInstance()
{
    if (instance == 0)
    {
        instance = new GarbageCollector;
        std::thread first(&GarbageCollector::threadRun, instance);
        first.detach();
    }
    return instance;
}

List * GarbageCollector::getList() {
    mutex.lock();
    return this->listGarbageCollector;
}

// Factory method to create objects of different types.
// Change is required only in this function to create a new object type

void GarbageCollector::deleteReferences(int ID){
    getList()->deleteReferences(ID);
    mutex.unlock();

};
void GarbageCollector::addReferences(int ID){
    getList()->addReferences(ID);
    mutex.unlock();

};

int GarbageCollector::getReferences(int ID) {
    int references = GarbageCollector::getInstance()->getList()->getNode(ID)->getReferences();
    mutex.unlock();
    return references;
}

int GarbageCollector::addNode( void* ptr, string type){
    int id =getList()->addNode(ptr, type);
    mutex.unlock();
    return id;
};

void GarbageCollector::setMemory(void *dirMemory, int ID, string theType){

    string address;
    string value;
    if(theType=="b"){
        value = to_string(*static_cast<bool*>(dirMemory));
    }else if(theType=="d"){
        value = to_string(*static_cast<double*>(dirMemory));;
    }else if(theType=="i"){
        value = to_string(*static_cast<int*>(dirMemory));
    }else if(theType=="f"){
        value = to_string(*static_cast<float*>(dirMemory));
    }else{
        value = *static_cast<std::string*>(dirMemory);
    }
    getList()->getNode(ID)->setDirMemory(dirMemory);
    mutex.unlock();

    std::ostringstream addressh;
    addressh<< dirMemory;
    address = addressh.str();

};

void GarbageCollector::deleteVS(int ID, List* l){
    string id = to_string(ID);
    string theType = l->getNode(ID)->getType();

    void* dirMemory= l->getNode(ID)->getDirMemory();
    if(theType=="b"){
        delete (static_cast<bool*>(dirMemory));
    }else if(theType=="d"){
        delete static_cast<double*>(dirMemory);;
    }else if(theType=="i"){
        delete static_cast<int*>(dirMemory);
    }else if(theType=="f"){
        delete static_cast<float*>(dirMemory);
    }else{
        delete static_cast<std::string*>(dirMemory);
    }

    l->deleteNode(ID);
}


[[noreturn]] void GarbageCollector::threadRun() {
    List *l=  getList();
    Node *present = l->getFirst();
    while(true){
        while (present != nullptr) {
            if (present->getReferences() == 0) {
                deleteVS(present->getID(), l);
                present = l->getFirst();
            } else{
                present = present->next;
            }
        }
        mutex.unlock();
        this_thread::sleep_for (chrono::milliseconds (50));
        present = getList()->getFirst();
    }
};
