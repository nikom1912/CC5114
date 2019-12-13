//
// Created by nikom on 12-12-2019.
//

#ifndef T3_AST_H
#define T3_AST_H

#include <vector>
#include "Node.h"
#include "NodeFactory.h"
#include <random>
#include "TerminalNode.h"

std::random_device rd;
std::mt19937 gen(rd());

template <typename T>
class AST {
private:
    std::vector<NodeFactory<T>*>* functions;
    std::vector<T>* terminals;
    double prob;
public:
    AST(std::vector<NodeFactory<T>*>* allowed_functions, std::vector<T>* allowed_terminals, double prob_terminal);
    Node<T>* create_rec_tree(int depth=10){
        if(depth > 0){
            std::uniform_int_distribution<unsigned long long> dis(0, functions->size() - 1);
            std::uniform_int_distribution<unsigned long long> dis2(0, 100);
            auto f = functions->at(dis(gen))->buildNode();
            auto args = new std::vector<Node<T>*>();
            for(int i = 0; i < f->num_arguments; i++ ){
                if(dis2(gen)/100.0 < prob)
                    args->push_back(create_rec_tree(0));
                else
                    args->push_back(create_rec_tree(depth - 1));
            }
            f->setArgs(args);
            return f;
        }
        else{
            return new TerminalNode<T>(terminals->at(rand()%terminals->size()));
        }
    }


};

template<typename T>
AST<T>::AST(std::vector<NodeFactory<T>*>* allowed_functions, std::vector<T>* allowed_terminals, double prob_terminal) {
    functions = allowed_functions;
    terminals = allowed_terminals;
    prob = prob_terminal;
}



#endif //T3_AST_H
