//
// Created by nikom on 11-12-2019.
//

#ifndef T3_ADDNODE_H
#define T3_ADDNODE_H

#include "BinaryNode.h"

template <typename T>
T _add(std::vector<T>* a){
    T res = a->at(0);
    for(auto el = a->begin() + 1; el != a->end(); el++){
        res += *el;
    }
    return res;
}

template <typename T>
class AddNode: public BinaryNode<T> {
public:
    AddNode() : BinaryNode<T>(_add) {}
    AddNode(Node<T>* left, Node<T>* right);
    AddNode(std::vector<Node<T>*>* args);


    void print();
};

template<typename T>
AddNode<T>::AddNode(Node<T>* left, Node<T> *right): BinaryNode<T>(_add, left, right){
}

template<typename T>
AddNode<T>::AddNode(std::vector<Node<T>*>* args):BinaryNode<T>(_add, args) {

}

template<typename T>
void AddNode<T>::print() {
    this->arguments->at(0)->print();
    std::cout << " + ";
    this->arguments->at(1)->print();
}


#endif //T3_ADDNODE_H
