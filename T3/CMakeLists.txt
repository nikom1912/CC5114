cmake_minimum_required(VERSION 3.14)
project(T3)

set(CMAKE_CXX_STANDARD 14)

set(NODE
        Node.h
        utils.cpp
        BinaryNode.h
        AddNode.h
        SubNode.h
        MaxNode.h
        MultNode.h
        TerminalNode.h
        AST.h
        NodeFactory.h
        GP.h
        )

add_executable(T3 num_con_repeticiones.cpp ${NODE})