#pragma once
#include "doctest.h"

#include "binary_tree.h"
#include "example_func.h"
#include "exceptions.h"


TEST_CASE("test_binary_tree_insert_contains") {
    BinaryTree<int> tree;
    
    tree.insert(5);
    CHECK(tree.contains(5));
    
    tree.insert(3);
    tree.insert(7);
    CHECK(tree.contains(3));
    CHECK(tree.contains(7));
    CHECK(!tree.contains(10));
}

TEST_CASE("test_binary_tree_find_min_max") {
    BinaryTree<int> tree;

    CHECK_THROWS_AS(tree.FindMin(), IndexOutOfRange);
    CHECK_THROWS_AS(tree.FindMax(), IndexOutOfRange);
    
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    
    CHECK(tree.FindMin() == 1);
    CHECK(tree.FindMax() == 7);
}

TEST_CASE("test_binary_tree_remove") {
    BinaryTree<int> tree;
    
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    
    tree.remove(3);
    CHECK(!tree.contains(3));
    CHECK(tree.contains(5));
    CHECK(tree.contains(7));
}

TEST_CASE("test_binary_tree_get_subtree") {
    BinaryTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    
    BinaryTree<int>* subtree = tree.GetSubtree(5);
    CHECK(subtree->contains(5));
    CHECK(subtree->contains(3));
    CHECK(subtree->contains(7));
    delete subtree;
}

TEST_CASE("test_binary_tree_is_subtree") {
    BinaryTree<int> tree1;
    tree1.insert(5);
    tree1.insert(3);
    tree1.insert(7);
    tree1.insert(1);
    tree1.insert(4);
    
    BinaryTree<int> tree2;
    tree2.insert(3);
    tree2.insert(1);
    tree2.insert(4);
    
    CHECK(tree1.IsSubtree(&tree2));
    
    BinaryTree<int> tree3;
    tree3.insert(3);
    tree3.insert(1);
    tree3.insert(6);
    
    CHECK(!tree1.IsSubtree(&tree3));
    
    BinaryTree<int> emptyTree;
    CHECK(emptyTree.IsSubtree(&emptyTree));
    CHECK(!emptyTree.IsSubtree(&tree1));
    CHECK(tree1.IsSubtree(&emptyTree));
}

TEST_CASE("test_binary_tree_map") {
    BinaryTree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    
    tree.map(map_example1);
    
    CHECK(tree.FindMin() == 2);
    CHECK(tree.FindMax() == 6);
    CHECK(tree.contains(4));
}

TEST_CASE("test_binary_tree_where") {
    BinaryTree<int> tree;
    for(int i = -3; i <= 6; i++) tree.insert(i);
    
    tree.where(where_example1);
    
    CHECK(tree.contains(1));
    CHECK(tree.contains(2));
    CHECK(!tree.contains(0));
    CHECK(!tree.contains(-1));
    CHECK(tree.FindMin() == 1);
}

TEST_CASE("test_binary_tree_reduce") {
    BinaryTree<int> tree;
    for(int i = 1; i <= 5; ++i) tree.insert(i);
    
    int sum = tree.reduce(reduce_example2, 0);
    int product = tree.reduce(reduce_example1, 1);
    
    CHECK(sum == 15);
    CHECK(product == 120);
}


TEST_CASE("test_binary_tree_from_to_string") {
    BinaryTree<int>* tree = BinaryTree<int>::FromString("{5}({3}()[])[{7}()[]]", "{N}(L)[R]");
    CHECK(tree->contains(5));
    CHECK(tree->contains(3));
    CHECK(tree->contains(7));
    
    std::string str = tree->ToString("{L](N)[R}");
    CHECK(str == "{{](3)[}](5)[{](7)[}}");
    delete tree;
}