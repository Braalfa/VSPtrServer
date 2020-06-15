//
// Created by usuario on 25/5/20.
//

#include "List.h"
#include "iostream"

using namespace std;

/**
 * Metodo para obtener el primer elemento de la lista
 * @return Primero nodo almacenado en la lista
 */
Node *List::getFirst()  {
    return first;
}

/**
 * Funcion para agregar nodo a la lista
 * @param dirMemory Nueva direccion de memoria a agregar
 * @param type Typo de dicha direccion de memoria
 * @return Retorna el ID del Node
 */
int List::addNode(void *dirMemory, string type) {
    if(this->first == nullptr){
        this->first = new Node(dirMemory, type);
        return this->first->getID();
    }
    else{
        Node *present = this->first;
        while(present->next != nullptr){
            present = present->next;
        }
        present->next = new Node(dirMemory, type);
        return present->next->getID();

    }
}

/**
 * Metodo para hacen un print en pantalla de los contenidos
 */
void List::printList() {
    Node *present = this->first;
    cout<<"{";
    while (present != nullptr) {
        cout<<present->getDirMemory();
        cout<<"->";
        cout<<present->getReferences();
        cout<<"->";
        cout<<present->getID();
        cout<<"/";
        present = present->next;
    }
    cout<<"}";
}

List::List() {
    first= nullptr;
}


/**
 * Metodo para eliminar nodo
 * @param ID Id del nodo a eliminar
 */
void List::deleteNode(int ID) {
    Node *temp1 = this->first;
    Node *temp2 = this->first->next;
    if(temp1->getID() == ID){
        this->first = temp1->next;
    }
    else{
        while(temp2->getID() != ID){
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        Node *aux = temp2;
        temp1->next = temp2->next;
        delete aux;
    }
}

/**
 * Metodo para obtener nodo
 * @param ID Id del nodo a obtener
 * @return Retorna el nodo buscado
 */
Node* List::getNode(int ID) {
    Node *present = this->first;
    while (present != nullptr){
        if(present->getID() == ID){
            return present;
        } else{
            present = present->next;
        }
    }
}


/**
 * Metodo para eliminar una referencia a un nodo
 * @param ID Id del nodo al cual se le elimina la referencia
 */
void List::deleteReferences(int ID) {
    Node* present = getNode(ID);
    present->deleteReferences();
}

/**
 * Metodo para agregar una referencia a un nodo
 * @param ID Id del nodo al cual se le agrega la referencia
 */
void List::addReferences(int ID) {
    Node* present = getNode(ID);
    present->addReferences();
}

/**
 * Metodo para cambiar la direccion de memoria de un Nodo
 * @param dirMemory Direccion de memoria nueva
 * @param ID Id del nodo a editar
 */
void List::setMemory(void *dirMemory, int ID) {
    Node* present = getNode(ID);
    present->setDirMemory(dirMemory);
}
