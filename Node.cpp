//
// Created by usuario on 25/5/20.
//

#include "Node.h"
#include "string"
#include "iostream"

using namespace std;

/**
 * Metodo para obtener el puntero del dato almacenado
 * @return Puntero void del dato almacenado
 */
void *Node::getDirMemory()  {
    return dirMemory;
}

/**
 * Metodo para vambiar el puntero almacenado
 * @param dirMemory  Nuevo puntero
 */
void Node::setDirMemory(void *dirMemory) {
    this->dirMemory = dirMemory;
    cout<<this->dirMemory<<endl;
    cout<<this->ID<<endl;

}
/**
 * Metodo para obtener las referencias de un nodo
 * @return Cantidad de referencias
 */
int Node::getReferences() {
    return this->references;
}


/**
 * Metodo para eliminar una referencia
 */
void Node::deleteReferences() {
    this->references = references-1;
}


/**
 * Metodo para aumentar en una las referencias
 */
void Node::addReferences() {
    this->references = references+1;
}

/**
 * Constructor del nodo
 */
Node::Node() {
    next = nullptr;
}


/**
 * Metodo constructor con datos
 * @param dirMemory Puntero a guardar
 * @param type Typo del dato almacenado en el puntero
 */
Node::Node(void *dirMemory, string type) {
    next = nullptr;
    this->dirMemory = dirMemory;
    this->ID = generateID();
    this->references = 1;
    this->type= type;
}

/**
 * Metodo generador de ID
 * @return Nuevo ID
 */
int Node::generateID() {
    static int i;
    i = i+1;
    int y= i;
    return y;
}

/**
 * Metodo para obtener el ID
 * @return Id del nodo
 */
int Node::getID() {
    return this->ID;
}

/**
 * Metodo para cambiar el tipo de dato al que apunta el puntero almacenado
 * @param type Nuevo tipo
 */
void Node::setType(string type){
    this->type= type;
}

/**
 * Metodo para retornar el tipo de dato almacenado
 * @return Un string con el tipo de dato almacenado
 */
string Node::getType(){
    return this->type;
}