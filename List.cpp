//
// Created by usuario on 25/5/20.
//

#include "List.h"
#include "iostream"

using namespace std;


Node *List::getFirst()  {
    return first;
}

int List::addNode(void *dirMemory) {
    if(this->first == nullptr){
        this->first = new Node(dirMemory);
        return this->first->getID();
    }
    else{
        Node *present = this->first;
        while(present->next != nullptr){
            present = present->next;
        }
        present->next = new Node(dirMemory);
        return present->next->getID();

    }
}

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

void List::deleteReferences(int ID) {
    Node* present = getNode(ID);
    present->deleteReferences();
}

void List::addReferences(int ID) {
    Node* present = getNode(ID);
    present->addReferences();
}

void List::setMemory(void *dirMemory, int ID) {
    Node* present = getNode(ID);
    present->setDirMemory(dirMemory);
}
