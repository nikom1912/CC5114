//
// Created by nikom on 10-12-2019.
//

#ifndef T3_NODE_H
#define T3_NODE_H

#include "utils.cpp"
#include <iostream>
#include <vector>


template <typename T>
class Node {
public:
    T (*operation)(std::vector<T>* args);
    int num_arguments;
    std::vector<Node<T>*> *arguments;
    Node<T> * parent;

    Node();
    Node(T (*op)(std::vector<T>* args));
    Node(T (*op)(std::vector<T>* args), std::vector<Node<T>*>* arguments);

    virtual T eval();
    std::vector<Node*>* serialize();
    Node<T>** serialize2();

    Node* copy();
    void replace(Node* n);
    void addArg(Node* n);
    int countNodes();
    virtual void setArgs(std::vector<Node<T>*>* args);

    virtual void print(){};

};

template<typename T>
Node<T>::Node(T (*op)(std::vector<T>*)) {
    operation = op;
    arguments = new std::vector<Node<T>*>();
    num_arguments = 0;
    parent = nullptr;
}

template<typename T>
T Node<T>::eval() {
    auto aux = new std::vector<T>();
    for(auto el = arguments->begin(); el != arguments->end(); el++){
        aux->push_back((*el)->eval());
    }
    return operation(aux);
}

template<typename T>
std::vector<Node<T>*>* Node<T>::serialize() {
    auto a = new std::vector<Node<T>*>();
//    std::cout << a->size() << "      " << a->max_size() << std::endl;
    a->push_back(this);
    if(this->arguments != nullptr) {
        for (auto el = this->arguments->begin(); el != this->arguments->end(); el++) {
            std::cout << std::endl;
            std::cout << (*el)->countNodes() << std::endl;
            my_extend(a, (*el)->serialize());
        }
    }
    return a;
}

template<typename T>
Node<T>* Node<T>::copy() {
    auto n = new Node<T>(operation);
    n->num_arguments = num_arguments;
    if(arguments != nullptr) {
        n->arguments = new std::vector<Node<T>*>();
        for (auto el = arguments->begin(); el != arguments->end(); el++) {
            Node<T> *newN = (*el)->copy();
            newN->parent = n;
            n->arguments->push_back(newN);
        }
    }
    n->parent = parent;
    return n;
}

template<typename T>
void Node<T>::replace(Node<T>* n) {
    if(this->parent == nullptr){
        this->operation = n->operation;
        this->arguments = n->arguments;
        this->num_arguments = n->num_arguments;
    }
    else{
        std::vector<Node*> *a = this->parent->arguments;
        for(auto el = a->begin(); el != a->end(); el++){
            if(*el == this){
                n->parent = this->parent;
                *el = n;

                return;
            }
        }
    }
}

template<typename T>
void Node<T>::addArg(Node* n) {
    n->parent = this;
    arguments->push_back(n);
    num_arguments++;
}

template<typename T>
Node<T>::Node(T (*op)(std::vector<T>*), std::vector<Node<T>*>* arguments) {
    this(op);
    num_arguments = 0;
    this->arguments = arguments;
    for(auto el = arguments->begin(); el != arguments->end(); el++){
        (*el)->parent = this;
    }
    this->num_arguments = arguments->size();
}

template<typename T>
int Node<T>::countNodes() {
    int res = 1;

    if(arguments != nullptr){
//        for(auto el = arguments->begin(); el != arguments->end(); el++){
//            res += (*el)->countNodes();
//        }
        for(int i = 0; i < num_arguments; i++)
            res += arguments->at(i)->countNodes();
    }
    return res;
}

template<typename T>
Node<T>::Node() {
    operation = nullptr;
    arguments = nullptr;
    num_arguments = 0;
    parent = nullptr;
}

template<typename T>
void Node<T>::setArgs(std::vector<Node<T> *> *args) {
    arguments = args;
    num_arguments = args->size();
    for(auto el = args->begin(); el != args->end(); el++){
        (*el)->parent = this;
    }
}

template<typename T>
Node<T> **Node<T>::serialize2() {
}


#endif //T3_NODE_H
