#include <fstream>
#include <chrono>
#include <random>

#include "binary_tree.h"
#include "example_func.h"

void stress_tests_insert() {
    std::ofstream insertFile("insert.txt");
    std::ofstream containsFile("contains.txt");
    std::ofstream removeFile("remove.txt");

    BinaryTree<int> *tree = new BinaryTree<int>();
    const int NUM_ELEMENTS = 1000000;
    const int STEP_ELEMENTS = NUM_ELEMENTS / 100;

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(INT_MIN, INT_MAX);

    for (int i = 0; i < NUM_ELEMENTS / STEP_ELEMENTS; i++) {

        auto duration_insert = std::chrono::nanoseconds(0);
        auto duration_contains = std::chrono::nanoseconds(0);
        auto duration_remove = std::chrono::nanoseconds(0);

        for (int j = 0; j < STEP_ELEMENTS; j++) {
            int value = dist(rng);

            auto start_insert_1 = std::chrono::high_resolution_clock::now();
            tree->insert(value);
            auto end_insert_1 = std::chrono::high_resolution_clock::now();
            duration_insert += std::chrono::duration_cast<std::chrono::nanoseconds>(end_insert_1 - start_insert_1);

            auto start_contains_1 = std::chrono::high_resolution_clock::now();
            tree->contains(value);
            auto end_contains_1 = std::chrono::high_resolution_clock::now();
            duration_contains += std::chrono::duration_cast<std::chrono::nanoseconds>(end_contains_1 - start_contains_1);

            
            auto start_remove_1 = std::chrono::high_resolution_clock::now();
            tree->remove(value);
            auto end_remove_1 = std::chrono::high_resolution_clock::now();
            duration_remove += std::chrono::duration_cast<std::chrono::nanoseconds>(end_remove_1 - start_remove_1);
            tree->insert(value);
        }
        
        insertFile << (i + 1) * STEP_ELEMENTS << " " << duration_insert.count() / STEP_ELEMENTS << "\n";
        containsFile << (i + 1) * STEP_ELEMENTS << " " << duration_contains.count() / STEP_ELEMENTS << "\n";
        removeFile << (i + 1) * STEP_ELEMENTS << " " << duration_remove.count() / STEP_ELEMENTS << "\n";
    }
    insertFile.close();
    containsFile.close();
    removeFile.close();
}

void stress_tests_pass() {
    std::ofstream passFile("pass.txt");
    std::ofstream whereFile("where.txt");
    std::ofstream copyFile("copy.txt");
    std::ofstream deleteFile("delete.txt");

    BinaryTree<int> *tree = new BinaryTree<int>();
    const int NUM_ELEMENTS = 100000;
    const int STEP_ELEMENTS = NUM_ELEMENTS / 100;

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(INT_MIN, INT_MAX);

    for (int i = 0; i < NUM_ELEMENTS / STEP_ELEMENTS; i++) {


        for (int j = 0; j < STEP_ELEMENTS; j++) {
            int value = dist(rng);
            tree->insert(value);
        }
        
        auto start_pass = std::chrono::high_resolution_clock::now();
        tree->reduce([](int a, int b) {return a * b; }, 0);
        auto end_pass = std::chrono::high_resolution_clock::now();
        auto duration_pass = std::chrono::duration_cast<std::chrono::nanoseconds>(end_pass - start_pass);
        
        BinaryTree<int> *where_tree = tree->Copy();
        auto start_where = std::chrono::high_resolution_clock::now();
        where_tree->where([](int value) {return value % 10 < 5; });
        auto end_where = std::chrono::high_resolution_clock::now();
        auto duration_where = std::chrono::duration_cast<std::chrono::nanoseconds>(end_where - start_where);
        delete where_tree;

        auto start_copy = std::chrono::high_resolution_clock::now();
        BinaryTree<int> *new_tree = tree->Copy();
        auto end_copy = std::chrono::high_resolution_clock::now();
        auto duration_copy = std::chrono::duration_cast<std::chrono::nanoseconds>(end_copy - start_copy);
        
        auto start_delete = std::chrono::high_resolution_clock::now();
        delete new_tree;
        auto end_delete = std::chrono::high_resolution_clock::now();
        auto duration_delete = std::chrono::duration_cast<std::chrono::nanoseconds>(end_delete - start_delete);

        passFile << (i + 1) * STEP_ELEMENTS << " " << duration_pass.count() / STEP_ELEMENTS << "\n";
        whereFile << (i + 1) * STEP_ELEMENTS << " " << duration_where.count() / STEP_ELEMENTS << "\n";
        copyFile << (i + 1) * STEP_ELEMENTS << " " << duration_copy.count() / STEP_ELEMENTS << "\n";
        deleteFile << (i + 1) * STEP_ELEMENTS << " " << duration_delete.count() / STEP_ELEMENTS << "\n";

    }
    passFile.close();
    whereFile.close();
    copyFile.close();
    deleteFile.close();
}

int main() {
    stress_tests_insert();
    stress_tests_pass();

    system("gnuplot -e \"plot 'insert.txt' with lines title 'Insert', "
        "'contains.txt' with lines title 'Contains', "
        "'remove.txt' with lines title 'Remove'; pause -1\"");
    
    system("gnuplot -e \"plot 'pass.txt' with lines title 'Pass', "
        "'where.txt' with lines title 'Where', "
        "'copy.txt' with lines title 'Copy', "
        "'delete.txt' with lines title 'Delete'; pause -1\"");
    /*
    system("gnuplot -e \"plot 'insert.txt' with lines title 'Insert'; pause -1\"");
    system("gnuplot -e \"plot 'contains.txt' with lines title 'Contains'; pause -1\"");
    system("gnuplot -e \"plot 'remove.txt' with lines title 'Remove'; pause -1\"");
    */
    return 0;
}