#pragma once

#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>

#include "exceptions.h"

template <typename T>
class BinaryTree {
private:
    struct TreeNode {
        T data;
        TreeNode *parent;
        TreeNode *left;
        TreeNode *right;
        TreeNode *next;
        int height;

        TreeNode(const T &value) :
            data(value),
            parent(nullptr),
            left(nullptr),
            right(nullptr),
            next(nullptr),
            height(1)
        {}
    };

    TreeNode *root;
    
    BinaryTree(TreeNode *root) : root(root) {}

    static int GetHeight(TreeNode* node) {
        return (node) ? node->height : 0;
    }

    static void UpdateHeight(TreeNode* node) {
        node->height = 1 + std::max(GetHeight(node->left), GetHeight(node->right));
    }


    static int BalanceFactor(TreeNode* node) {
        return GetHeight(node->right) - GetHeight(node->left);
    }

    static TreeNode* RotateRight(TreeNode *r) {
        TreeNode* l = r->left;
        r->left = l->right;
        if (l->right) l->right->parent = r;
        l->right = r;
        l->parent = r->parent;
        r->parent = l;
        UpdateHeight(r);
        UpdateHeight(l);
        return l;
    }

    static TreeNode* RotateLeft(TreeNode *l) {
        TreeNode* r = l->right;
        l->right = r->left;
        if (r->left) r->left->parent = l;
        r->left = l;
        r->parent = l->parent;
        l->parent = r;
        UpdateHeight(l);
        UpdateHeight(r);
        return r;
    }

    static TreeNode* balance(TreeNode *node) {
        int bf = BalanceFactor(node);
        
        if (bf == -2) {
            if (BalanceFactor(node->left) > 0) {
                node->left = RotateLeft(node->left);
            }
            return RotateRight(node);
        }
        else if (bf == 2) {
            if (BalanceFactor(node->right) < 0) {
                node->right = RotateRight(node->right);
            }
            return RotateLeft(node);
        }
        return node;
    }


    static void SetNextRecursive(TreeNode* node, TreeNode*& prev) {
        if (!node) {
            if (prev) prev->next = nullptr;
            return;
        }
        
        SetNextRecursive(node->left, prev);
        
        if (prev) prev->next = node;
        prev = node;
        
        SetNextRecursive(node->right, prev);
    }

    static void SetNext(TreeNode* root) {
        TreeNode* prev = nullptr;
        SetNextRecursive(root, prev);
    }


    static TreeNode* FindMin(TreeNode *node) {
        if (!node) return nullptr;
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    static TreeNode* FindMax(TreeNode *node) {
        if (!node) return nullptr;
        while (node->right) {
            node = node->right;
        }
        return node;
    }

    static TreeNode* FindInOrderSuccessor(TreeNode* node) {
        if (node->right) {
            return FindMin(node->right);
        }
        else {
            TreeNode* current = node;
            TreeNode* parent = current->parent;
            while (parent != nullptr && current == parent->right) {
                current = parent;
                parent = parent->parent;
            }
            return parent;
        }
    }

    static TreeNode* FindInOrderPredecessor(TreeNode* node) {
        if (node->left) {
            return FindMax(node->left);
        }
        else {
            TreeNode* current = node;
            TreeNode* parent = current->parent;
            while (parent != nullptr && current == parent->left) {
                current = parent;
                parent = parent->parent;
            }
            return parent;
        }
    }


    static TreeNode *CopyNode(const TreeNode* src, TreeNode* parent) {
        if (!src) return nullptr;
        TreeNode* new_node = new TreeNode(src->data);
        new_node->parent = parent;
        new_node->height = src->height;
        new_node->left = CopyNode(src->left, new_node);
        new_node->right = CopyNode(src->right, new_node);
        return new_node;
    };

    static BinaryTree *Copy(const TreeNode *node) {
        if (!node) return new BinaryTree();

        TreeNode* new_root = CopyNode(node, nullptr);
        BinaryTree* new_tree = new BinaryTree();
        new_tree->root = new_root;

        SetNext(new_root);
        return new_tree;
    }


    static TreeNode* insert(TreeNode* node, const T& value, TreeNode* parent, TreeNode** new_node) {
        if (!node) {
            *new_node = new TreeNode(value);
            (*new_node)->parent = parent;
            return *new_node;
        }
        else {
            if (value < node->data) {
                node->left = insert(node->left, value, node, new_node);
            }
            else if (value > node->data) {
                node->right = insert(node->right, value, node, new_node);
            }
            else {
                *new_node = nullptr;
                return node;
            }
        }
        UpdateHeight(node);
        return balance(node);
    }

    static TreeNode *remove(TreeNode *node, const T &value) {
        if (!node) return nullptr;

        else {
            if (value < node->data) {
                node->left = remove(node->left, value);
                if (node->left) node->left->parent = node;
            }
            else if (value > node->data) {
                node->right = remove(node->right, value);
                if (node->right) node->right->parent = node;
            }
            else {
                if (!node->left || !node->right) {
                    TreeNode* temp = (node->left) ? node->left : node->right;
                    if (temp) temp->parent = node->parent;
                    TreeNode* pred = FindInOrderPredecessor(node);
                    if (pred) pred->next = node->next;
                    delete node;
                    return temp;
                }
                else {
                    TreeNode *min_right = FindMin(node->right);
                    node->data = min_right->data;
                    node->right = remove(node->right, min_right->data);
                    if (node->right) node->right->parent = node;
                    node->next = FindInOrderSuccessor(node);
                }
            }
        }
        UpdateHeight(node);
        return balance(node);
    }

    static const TreeNode *find(const TreeNode *node, const T &value) {
        if (!node) return nullptr;
        if (value == node->data) {
            return node;
        }
        else if (value < node->data) {
            return find(node->left, value);
        }
        else {
            return find(node->right, value);
        }
    }


    static bool IsSame(const TreeNode* T1, const TreeNode* T2) {
        if (!T1 && !T2) return true;
        if (!T1 || !T2) return false;
        return (T1->data == T2->data) &&
            IsSame(T1->left, T2->left) &&
            IsSame(T1->right, T2->right);
    }

    static bool IsSubtree(const TreeNode* T1, const TreeNode* T2) {
        if (!T2) return true;
        if (!T1) return false;
        
        if (T1->data == T2->data && IsSame(T1, T2)) {
            return true;
        }
        
        if (T2->data < T1->data) {
            return IsSubtree(T1->left, T2);
        }
        else {
            return IsSubtree(T1->right, T2);
        }
    }

    static void print(TreeNode *node, int space = 0) {
        if (!node) return;
        space++;
        print(node->right, space);
        std::cout << std::endl;
        for (int i = 1; i < space; i++) std::cout << "    ";
        std::cout << node->data << "\n";
        print(node->left, space);
    }


    static std::string ToString(const TreeNode *node, const std::string format) {
        if (!node) return "";
        
        std::ostringstream ss;

        for (size_t i = 0; i < 3; i++) {
            ss << format[3 * i];
            if (format[3 * i + 1] == 'L') ss << ToString(node->left, format);
            else if (format[3 * i + 1] == 'R') ss << ToString(node->right, format);
            else ss << node->data;
            ss << format[3 * i + 2];
        }

        return ss.str();
    }

    static TreeNode* ParseNode(const std::string& str, const std::string& format, size_t& pos) {
        if (pos >= str.length()) return nullptr;

        T data = 0;
        TreeNode* left = nullptr;
        TreeNode* right = nullptr;

        for (size_t i = 0; i < 3; i++) {
            if (pos >= str.length() || str[pos] != format[3 * i])
                throw InvalidInput(str, "format error");
            pos++;

            if (format[3 * i + 1] == 'N') {
                size_t end = str.find(format[3 * i + 2], pos);
                if (end == std::string::npos)
                    throw InvalidInput(str, "format error");
                
                std::istringstream iss(str.substr(pos, end - pos));
                if (!(iss >> data))
                    throw InvalidInput(str, "number parsing error");
                pos = end + 1;
            }
            else if (format[3 * i + 1] == 'L') {
                if (str[pos] == format[0]) {
                    left = ParseNode(str, format, pos);
                }
                if (pos >= str.length() || str[pos] != format[3 * i + 2])
                    throw InvalidInput(str, "format error");
                pos++;
            }
            else if (format[3 * i + 1] == 'R') {
                if (str[pos] == format[0]) {
                    right = ParseNode(str, format, pos);
                }
                if (pos >= str.length() || str[pos] != format[3 * i + 2])
                    throw InvalidInput(str, "format error");
                pos++;
            }
        }

        TreeNode* node = new TreeNode(data);
        node->left = left;
        node->right = right;
        return node;
    }


    static void clear(TreeNode *node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    static size_t CountNodes(TreeNode* head) {
        size_t count = 0;
        TreeNode* current = head;
        while (current != nullptr) {
            current = current->next;
            count++;
        }
        return count;
    }

    static TreeNode* BuildBalanced(TreeNode*& head, size_t n, TreeNode* parent) {
        if (n == 0) return nullptr;
        
        TreeNode* left = BuildBalanced(head, n / 2, nullptr);
        
        TreeNode* root = head;
        root->parent = parent;
        root->left = left;
        if (left) left->parent = root;
        head = head->next;
        
        TreeNode* right = BuildBalanced(head, n - (n / 2 + 1), root);
        root->right = right;
        if (right) right->parent = root;
        
        UpdateHeight(root);
        return root;
    }

    static void BalanceForce(TreeNode *&root, TreeNode *head) {
        if (!root) return;
        
        size_t nodeCount = CountNodes(head);
        root = BuildBalanced(head, nodeCount, nullptr);
        SetNext(root);
    }

public:
    BinaryTree() : root(nullptr) {}

    ~BinaryTree() {
        TreeNode *node = FindMin(root);
        while (node) {
            TreeNode *toDelete = node;
            node = node->next;
            delete toDelete;
        }
    }

    void insert(const T &value) {
        TreeNode* new_node = nullptr;
        root = insert(root, value, nullptr, &new_node);
        if (new_node) {
            TreeNode* pred = FindInOrderPredecessor(new_node);
            TreeNode* succ = FindInOrderSuccessor(new_node);
            new_node->next = succ;
            if (pred) pred->next = new_node;
        }
    }

    void remove(const T &value) {
        root = remove(root, value);
    }

    bool contains(const T &value) const {
        return find(root, value) != nullptr;
    }

    T FindMin() const {
        TreeNode *node = FindMin(root);
        if (!node) throw IndexOutOfRange(0, 0);
        return node->data;
    }
    
    T FindMax() const {
        TreeNode *node = FindMax(root);
        if (!node) throw IndexOutOfRange(0, 0);
        return node->data;
    }

    BinaryTree *GetSubtree(const T &value) const {
        return Copy(find(root, value));
    }

    BinaryTree *Copy() const {
        return Copy(root);
    }

    bool IsSubtree(const BinaryTree *subtree) const {
        return IsSubtree(root, subtree->root);
    }

    void print() const {
        print(root);
    }

    std::string ToString(const std::string format) const {
        return ToString(root, format);
    }

    static BinaryTree* FromString(const std::string& str, const std::string& format) {
        size_t pos = 0;
        TreeNode* root = ParseNode(str, format, pos);
        if (pos != str.length()) {
            delete root;
            throw InvalidInput(str, "extra characters at the end");
        }

        SetNext(root);
        TreeNode* current = FindMin(root);
        while (current && current->next) {
            if (current->data >= current->next->data)
                throw InvalidInput(str, "this binary tree is not BST");
            current = current->next;
        }

        BalanceForce(root, FindMin(root));
        return new BinaryTree(root);
    }

    void map(T (*func)(T)) {
        TreeNode *curr = FindMin(root);
        while (curr) {
            curr->data = func(curr->data);
            curr = curr->next;
        }
    }

    void where(bool (*func)(T)) {
        TreeNode *curr = FindMin(root);
        TreeNode *head = curr;
        TreeNode *prev = nullptr;
        TreeNode *toDelete;
        while (curr) {
            if (!func(curr->data)) {
                if (prev == nullptr) {
                    head = curr->next;
                }
                else {
                    prev->next = curr->next;
                }
                toDelete = curr;
                curr = curr->next;
                delete toDelete;
            }
            else {
                prev = curr;
                curr = curr->next;
            }
        }
        BalanceForce(root, head);
    }

    T reduce(T (*func)(T, T), T c) const {
        T result = c;
        TreeNode *current = FindMin(root);
        while (current) {
            result = func(current->data, result);
            current = current->next;
        }
        return result;
    }
};