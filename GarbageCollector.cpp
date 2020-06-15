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

/**
 * Incializa el grabage collecotr reisa el tipo de garvage el cual crea e inicializa una lista para guradar la infomracion
 * del vsptr
 */
GarbageCollector::GarbageCollector(){
    listGarbageCollector= new List;
}

/**
 * Al ser el garbageCollector creado por un singelton este solo genera una misma intacia
 * @return
 */
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
/**
 *
 * @return la lista donde se encuentran guardada la informacion de los vsptrs
 */
List * GarbageCollector::getList() {
    mutex.lock();
    return this->listGarbageCollector;
}


/**
 * ELimina una referencia al VSPtr que pisea esa referencia
 * @param ID elimina una referencia en los ID
 */
void GarbageCollector::deleteReferences(int ID){
    getList()->deleteReferences(ID);
    mutex.unlock();

};

/**
 * Añade una refencia al nodo en la lista que pose ese ID en especifico
 * @param ID el valaor unico para todos los VSPtr
 */
void GarbageCollector::addReferences(int ID){
    getList()->addReferences(ID);
    mutex.unlock();

};



int GarbageCollector::getReferences(int ID) {
    int references = GarbageCollector::getInstance()->getList()->getNode(ID)->getReferences();
    mutex.unlock();
    return references;
}

/**
 * Añade un nuevo nodo a la lista enlazada
 * @param ptr la direccion de memeoria que se añade a ls lista
 * @param type el tipode dato que es añadidp
 * @return
 */
int GarbageCollector::addNode( void* ptr, string type){
    int id =getList()->addNode(ptr, type);
    mutex.unlock();
    return id;
};

/**
 * Metodo para generar el puntero de cierto ID
 * @param dirMemory Puntero que se agregara a la lista
 * @param ID ID del puntero
 * @param theType Tipo de dato almacenado en el puntero
 */

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
/**
 * Funcion que se utiliza pra elimitar un vsptr especifico
 * @param ID el ID del VSPtr especifica que quiero elimiar
 * @param l la lista con los vsptr creados
 */
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

/**
 * Este es un hilo el cual se ejecuta para la eliminacion de los nodos los cuales llegan a 0 refenrecias
 */
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
