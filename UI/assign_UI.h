#pragma once

#include "binary_tree.h"
#include "creation_UI.h"
#include "binary_tree_UI.h"


template <typename T>
void AssignUI() {
    BinaryTree<T> *tree = new BinaryTree<T>();
    tree = CreationUI<T>();
    BinaryTreeUI<T>(tree);
}
