//
// Created by nikom on 12-12-2019.
//

#ifndef T3_SUBNODE_H
#define T3_SUBNODE_H


#include "BinaryNode.h"

template <typename T>
T _sub(std::vector<T>* a){
    T res = a->at(0);
    for(auto el = a->begin() + 1; el != a->end(); el++){
        res -= *el;
    }
    return res;
}

template <typename T>
class SubNode: public BinaryNode<T> {
public:
    SubNode() : BinaryNode<T>(_sub) {}
    SubNode(Node<T>* left, Node<T>* right);
    SubNode(std::vector<Node<T>*>* args);

    void print();
};

template<typename T>
SubNode<T>::SubNode(Node<T>* left, Node<T>* right): BinaryNode<T>(_sub, left, right){

}

template<typename T>
SubNode<T>::SubNode(std::vector<Node<T>*>* args):BinaryNode<T>(_sub, args) {

}

template<typename T>
void SubNode<T>::print() {
    this->arguments->at(0)->print();
    std::cout << " - ";
    this->arguments->at(1)->print();

}


#endif //T3_SUBNODE_H
