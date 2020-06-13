//
// Created by usuario on 22/5/20.
//

#include <sstream>
#include "GarbageCollector.h"
#include "iostream"

GarbageCollector* GarbageCollector::instance = 0;

GarbageCollector::GarbageCollector(){
    listGarbageCollector= new List;
}


GarbageCollector* GarbageCollector::getInstance()
{
    if (instance == 0)
    {
        instance = new GarbageCollector;
    }
    return instance;
}

List * GarbageCollector::getList() {
    return this->listGarbageCollector;
}

// Factory method to create objects of different types.
// Change is required only in this function to create a new object type

void GarbageCollector::deleteReferences(int ID){
    getList()->deleteReferences(ID);
    if (getList()->getNode(ID)->getReferences()==0) {
        deleteVS(ID);
    }
};
void GarbageCollector::addReferences(int ID){
    getList()->addReferences(ID);
};

int GarbageCollector::addNode( void* ptr, string type){
    int id =getList()->addNode(ptr);
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
    std::ostringstream addressh;
    addressh<< dirMemory;
    address = addressh.str();

};

void GarbageCollector::deleteVS(int ID){
    string id = to_string(ID);
    delete(getList()->getNode(ID)->getDirMemory());
    getList()->deleteNode(ID);
}