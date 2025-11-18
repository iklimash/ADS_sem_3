cmake_minimum_required(VERSION 4.0)
project(lab_3)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab_3 main.cpp
        binaryTree.h tree.txt
        AVLTree.h)
configure_file(tree.txt tree.txt COPYONLY)