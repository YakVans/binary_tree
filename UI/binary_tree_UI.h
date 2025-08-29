#pragma once

#include <iostream>
#include <string>

#include "manual_read.h"

#include "binary_tree.h"

#include "save_or_not_UI.h"
#include "map_where_reduce_UI.h"
#include "creation_UI.h"

template <typename T>
void *BinaryTreeUI(BinaryTree<T> *&tree) {
    std::cout << "--- Operations ---\n" <<
        "0. Delete and back to menu\n"
        "\n"
        "1. Print tree\n"
        "2. Check contains\n"
        "3. Find min\n"
        "4. Find max\n"
        "5. Get subtree\n"
        "6. Is subtree\n"
        "\n"
        "7. Insert element\n"
        "8. Remove element\n"
        "\n"
        "9. Map\n"
        "10. Where\n"
        "11. Reduce\n"
        "\n"
        "12. Form string\n";
    while (true) {
        try {
            std::cout << "\nOperation: ";
            size_t operation = ReadOne<size_t>();
            
            if (operation == 0) {
                delete tree;
                return nullptr;
            }
            else {
                switch (operation) {
                    case 1: {
                        std::cout << "Current tree:";
                        tree->print();
                        break;
                    }
                    case 2: {
                        std::cout << "Check value: ";
                        T value = ReadOne<T>();
                        if (tree->contains(value)) std::cout << "contains\n";
                        else std::cout << "not contains\n";
                        break;
                    }
                    case 3: {
                        std::cout << "Min: " << tree->FindMin() << "\n";
                        break;
                    }
                    case 4: {
                        std::cout << "Max: " << tree->FindMax() << "\n";
                        break;
                    }
                    case 5: {
                        std::cout << "Get subtree from value: ";
                        T value = ReadOne<T>();
                        BinaryTree<T> *subtree = tree->GetSubtree(value);
                        subtree->print();
                        if (SaveOrNot(subtree)) {
                            delete tree;
                            tree = subtree;
                        }
                        break;
                    }
                    case 6: {
                        std::cout << "Checked subtree: ";
                        BinaryTree<T> *subtree = CreationUI<T>();
                        if (tree->IsSubtree(subtree)) std::cout << "Include this\n";
                        else std::cout << "Not include this\n";
                        delete subtree;
                        break;
                    }
                    case 7: {
                        std::cout << "Insert value: ";
                        T value = ReadOne<T>();
                        tree->insert(value);
                        break;
                    }
                    case 8: {
                        std::cout << "Remove value: ";
                        T value = ReadOne<T>();
                        tree->remove(value);
                        break;
                    }
                    case 9: {
                        MapUI<T>(tree);
                        break;
                    }
                    case 10: {
                        WhereUI<T>(tree);
                        break;
                    }
                    case 11: {
                        std::cout << "Reduced: " << ReduceUI<T>(tree) << "\n";
                        break;
                    }
                    case 12: {
                        std::string format;

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

                        std::cout << tree->ToString(format) << "\n";
                        break;
                    }
                    default: {
                        throw InvalidInput(std::to_string(operation), "Wrong index of operation");
                        break;
                    }
                }
            }
        }
        catch (const std::logic_error &e) {
            std::cout << e.what();
        }
    }
}