//
// Created by usuario on 10/6/20.
//

#include "TNode.h"
#include "iostream"

using namespace std;
/**
 * Constructor del nodo
 */
TNode::TNode()
{
    next = nullptr;
}

/**
 * Constructor de clase
 * @param data Dato para inicializar la clase
 */
TNode::TNode(string data)
{
    next = nullptr;
    value = data;
}

/**
 * Metodo para obtener el valor guardado
 * @return string del valor guardado
 */
string TNode::getValue()
{
    return  value;
}

/**
 * Metodo para cambiar el valor guardadp
 * @param data Nuevo valor a guardar
 */
void TNode::setValue(string data) {
    this->value = data;
}
