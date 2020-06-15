//
// Created by usuario on 10/6/20.
//

#include "TNode.h"
#include "iostream"

using namespace std;

TNode::TNode()
{
    next = nullptr;
}


TNode::TNode(string data)
{
    next = nullptr;
    value = data;
}


string TNode::getValue()
{
    return  value;
}

void TNode::setValue(string data) {
    this->value = data;
}
