#pragma once

#include <iostream>
#include <string>

#include "binary_tree.h"


template <typename T>
BinaryTree<T> *CreationUI() {
    std::string format;
    std::string str;

    while (true) {
        try {
            std::cout << "\nFormat: ";
            std::getline(std::cin, format);
            if (format.length() != 9 ||
                (format[1] != 'L' && format[1] != 'R' && format[1] != 'N') ||
                (format[4] != 'L' && format[4] != 'R' && format[4] != 'N') ||
                (format[7] != 'L' && format[7] != 'R' && format[7] != 'N'))
            {
                throw InvalidInput(format, "format must have 9 length and"
                    "2, 5, 8 symbols must be permutation of L, R, N");
            }
            break;
        }
        catch (const InvalidInput &e) {
            std::cout << e.what() << "\n";
        }
    }
    while (true) {
        try {
            std::cout << "\nInput: ";
            std::getline(std::cin, str);
            BinaryTree<T> *tree = BinaryTree<T>::FromString(str, format);
            return tree;
        }
        catch (const InvalidInput &e) {
            std::cout << e.what() << "\n";
        }
    }
}