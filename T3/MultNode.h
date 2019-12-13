//
// Created by nikom on 12-12-2019.
//

#ifndef T3_MULTNODE_H
#define T3_MULTNODE_H

#include "BinaryNode.h"

template <typename T>
T _mult(std::vector<T>* a){
    T res = a->at(0);
    for(auto el = a->begin() + 1; el != a->end(); el++){
        res *= *el;
    }
    return res;
}

template <typename T>
class MultNode: public BinaryNode<T> {
public:
    MultNode() : BinaryNode<T>(_mult) {};
    MultNode(Node<T>* left, Node<T> *right);
    MultNode(std::vector<Node<T>*> *args);

    void print();
};

template<typename T>
MultNode<T>::MultNode(Node<T> *left, Node<T>* right): BinaryNode<T>(_mult, left, right){

}

template<typename T>
MultNode<T>::MultNode(std::vector<Node<T>*> *args): BinaryNode<T>(_mult, args) {

}

template<typename T>
void MultNode<T>::print() {
    this->arguments->at(0)->print();
    std::cout << " * ";
    this->arguments->at(1)->print();

}


#endif //T3_MULTNODE_H
