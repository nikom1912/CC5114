//
// Created by nikom on 12-12-2019.
//

#ifndef T3_NODEFACTORY_H
#define T3_NODEFACTORY_H

#include "AddNode.h"
#include "SubNode.h"
#include "MultNode.h"
#include "MaxNode.h"

template <typename T>
class NodeFactory {
private:
    int node_type;
public:
    NodeFactory(int type){
        node_type = type;
    }

    Node<T>* buildNode(){
        switch (node_type){
            case 1:
                return new AddNode<T>();
            case 2:
                return new SubNode<T>();
            case 3:
                return new MultNode<T>();
            case 4:
                return new MaxNode<T>();
        }
    }
};


#endif //T3_NODEFACTORY_H
