//
// Created by nikom on 12-12-2019.
//

#ifndef T3_TERMINALNODE_H
#define T3_TERMINALNODE_H

#include "Node.h"


template <typename T>
class TerminalNode: public Node<T> {
private:
    T value;
public:
    TerminalNode<T>(T value);
    T eval();
    void print();
};

template<typename T>
TerminalNode<T>::TerminalNode(T value): Node<T>(nullptr) {
    this->value = value;
    this->arguments = nullptr;
    this->num_arguments = 0;
}

template<typename T>
T TerminalNode<T>::eval() {
    return value;
}

template<typename T>
void TerminalNode<T>::print() {
    std::cout << value;
}


#endif //T3_TERMINALNODE_H
