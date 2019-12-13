//
// Created by nikom on 12-12-2019.
//

#ifndef T3_MAXNODE_H
#define T3_MAXNODE_H

#include "BinaryNode.h"

template <typename T>
T _max(std::vector<T> *a){
    T res = a->at(0);
    for(auto el = a->begin() + 1; el != a->end(); el++){
        if(*el > res){
            res = *el;
        }
    }
    return res;
}

template <typename T>
class MaxNode: public BinaryNode<T> {
public:
    MaxNode() : BinaryNode<T>(_max) {}
    MaxNode(Node<T>* left, Node<T>* right);
    MaxNode(std::vector<Node<T>*> *args);

    void print();
};

template<typename T>
MaxNode<T>::MaxNode(Node<T>* left, Node<T> *right): BinaryNode<T>(_max, left, right){

}

template<typename T>
MaxNode<T>::MaxNode(std::vector<Node<T>*>* args):BinaryNode<T>(_max, args) {

}

template<typename T>
void MaxNode<T>::print() {
    std::cout << "max(";
    this->arguments->at(0)->print();
    std::cout << " ,";
    this->arguments->at(1)->print();
    std::cout << ")";
}

#endif //T3_MAXNODE_H
