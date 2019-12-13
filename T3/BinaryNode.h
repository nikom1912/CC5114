//
// Created by nikom on 11-12-2019.
//

#ifndef T3_BINARYNODE_H
#define T3_BINARYNODE_H

#include "Node.h"

template <typename T>
class BinaryNode: public Node<T> {

public:
    BinaryNode(T (*op)(std::vector<T>*));
    BinaryNode(T (*op)(std::vector<T>*), Node<T>* left, Node<T>* right);
    BinaryNode(T (*op)(std::vector<T>*), std::vector<Node<T>*> *arguments);

    void setLeft(Node<T>* n);
    void setRight(Node<T>* n);

    void setArgs(std::vector<Node<T>*>* args);

};

template<typename T>
BinaryNode<T>::BinaryNode(T (*op)(std::vector<T>*), Node<T>* left, Node<T>* right): Node<T>(op) {

    this->addArg(left);
    this->addArg(right);
}

template<typename T>
void BinaryNode<T>::setRight(Node<T>* n) {
    n->parent = this;
    this->arguments->emplace(this->arguments->begin() + 1, n);
}

template<typename T>
void BinaryNode<T>::setLeft(Node<T>* n) {
    n->parent = this;
    this->arguments->emplace(this->arguments->begin(), n);
}

template<typename T>
BinaryNode<T>::BinaryNode(T (*op)(std::vector<T>*), std::vector<Node<T>*>* arguments):Node<T>(op) {
    if(arguments->size() == 2){
        this->arguments = arguments;
    }
}


template<typename T>
void BinaryNode<T>::setArgs(std::vector<Node<T> *> *args) {
    if(args->size() == 2){
        this->arguments = args;
        for(auto el = args->begin(); el != args->end(); el++){
            (*el)->parent = this;
        }
    }

}

template<typename T>
BinaryNode<T>::BinaryNode(T (*op)(std::vector<T> *)):Node<T>(op) {
    this->num_arguments = 2;

}

#endif //T3_BINARYNODE_H
