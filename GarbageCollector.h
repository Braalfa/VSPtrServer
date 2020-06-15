//
// Created by usuario on 22/5/20.
//

#ifndef VSCODEMEMORY_GARBAGECOLLECTOR_H
#define VSCODEMEMORY_GARBAGECOLLECTOR_H


#include "List.h"
#
/*
 * Aqui arriba va la clase sujeto del GarbageCollector, pero me puse a programar esa lista de mierda.
 *
 */

using namespace std;
#include <string>
#include <mutex>


enum GarbageType {
    Local,    Remote
};

/**
 * El garbage collector remoto es la clase que maneja la memoria en el servidor remoto, creando
 * punteros con los datos a almacenar y generando operaciones en estos, ademas de retornando informacion
 * valiosa
 * */
class GarbageCollector
{
protected:
    GarbageCollector();
    static GarbageCollector *instance;
    List *listGarbageCollector;

public:
    List * getList();

    static std::mutex mutex;
    void deleteReferences(int ID);
    int getReferences(int ID);
    void addReferences(int ID);
    int addNode( void* ptr, string type);
    void setMemory(void *dirMemory, int ID, string type);
    void deleteVS(int ID);
    static GarbageCollector* getInstance();
    [[noreturn]] void threadRun();

    void deleteVS(int ID, List *l);
};


#endif //VSCODEMEMORY_GARBAGECOLLECTOR_H
