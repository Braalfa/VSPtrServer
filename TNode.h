//
// Created by usuario on 10/6/20.
//

#ifndef VSCODEMEMORYLIB_TNODE_H
#define VSCODEMEMORYLIB_TNODE_H

#include <string>
using namespace std;


/**
 * Clase para guardar valores de una lista
 */
class TNode {
private:
    string value;
public:
    TNode *next;
    TNode();
    TNode(string value);
    string getValue();
    void setValue(string value);
};


#endif //VSCODEMEMORYLIB_TNODE_H
