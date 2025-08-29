#pragma once

#include <iostream>
#include <string>

#include "manual_read.h"
#include "example_func.h"
#include "binary_tree.h"

template <typename T>
void MapUI(BinaryTree<T> *tree) {
    size_t map_choice;
    std::cout << "Possible map:\n" <<
        "1. v * 2\n"
        "2. v + 1\n"
        "3. (v - 2) * 3\n";
    
    while (true) {
        try {
            std::cout << "\nMap choice: ";
            map_choice = ReadOne<size_t>();
            if (map_choice < 1 ||
                map_choice > 3) {
                throw InvalidInput(std::to_string(map_choice), "Selection must be in 1-3");
            }
            break;
        }
        catch (const InvalidInput &e) {
            std::cout << e.what();
        }
    }

    if (map_choice == 1) {
        tree->map(map_example1<T>);
    }
    else if (map_choice == 2) {
        tree->map(map_example2<T>);
    }
    else if (map_choice == 3) {
        tree->map(map_example3<T>);
    }
}

template <typename T>
void WhereUI(BinaryTree<T> *tree) {
    size_t where_choice;
    std::cout << "Possible where:\n" <<
        "1. v >= 1\n"
        "2. v == 0\n"
        "3. v < -3\n";
    
    while (true) {
        try {
            std::cout << "\nWhere choice: ";
            where_choice = ReadOne<size_t>();
            if (where_choice < 1 ||
                where_choice > 3) {
                throw InvalidInput(std::to_string(where_choice), "Selection must be in 1-3");
            }
            break;
        }
        catch (const InvalidInput &e) {
            std::cout << e.what();
        }
    }

    if (where_choice == 1) {
        tree->where(where_example1<T>);
    }
    else if (where_choice == 2) {
        tree->where(where_example2<T>);
    }
    else if (where_choice == 3) {
        tree->where(where_example3<T>);
    }
}

template <typename T>
T ReduceUI(BinaryTree<T> *tree) {
    size_t reduce_choice;
    std::cout << "Possible reduce:\n" <<
        "1. *\n"
        "2. +\n"
        "3. -\n";
    
    while (true) {
        try {
            std::cout << "\nReduce choice: ";
            reduce_choice = ReadOne<size_t>();
            if (reduce_choice < 1 ||
                reduce_choice > 3) {
                throw InvalidInput(std::to_string(reduce_choice), "Selection must be in 1-3");
            }
            break;
        }
        catch (const InvalidInput &e) {
            std::cout << e.what();
        }
    }

    if (reduce_choice == 1) {
        return tree->reduce(reduce_example1<T>, 1);
    }
    else if (reduce_choice == 2) {
        return tree->reduce(reduce_example2<T>, 0);
    }
    else if (reduce_choice == 3) {
        return tree->reduce(reduce_example3<T>, 0);
    }
    return 0;
}