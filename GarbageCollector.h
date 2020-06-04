//
// Created by usuario on 22/5/20.
//

#ifndef VSCODEMEMORY_GARBAGECOLLECTOR_H
#define VSCODEMEMORY_GARBAGECOLLECTOR_H

#include "List.h"


using namespace std;



class GarbageCollector
{
private:

    static GarbageCollector *instance;
    List *listGarbageCollector = new List();
public:
    GarbageCollector();
    List * getList();
    static GarbageCollector* getInstance();
    void threadRun() ;
    void deleteReferences(int ID);
    int addNode(void* ptr);
    void addReferences(int ID);
    void setMemory(void *dir, int ID);
};


#endif //VSCODEMEMORY_GARBAGECOLLECTOR_H
