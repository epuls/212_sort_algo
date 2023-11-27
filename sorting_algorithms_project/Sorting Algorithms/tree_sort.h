#ifndef TREE_SORT_TREE_SORT_H
#define TREE_SORT_TREE_SORT_H

#include <iostream>
#include <vector>

class Node{
private:
    int data;
    Node *left;
    Node *right;

public:
    Node(int d);
    ~Node();

    friend class TreeSort;
};

class TreeSort {
private:
    Node* root;
    void inorder(Node* n, std::vector<int> &vec, int &i);
    Node* insert(Node* n, int key);
    void destroy(Node* n);


public:
    TreeSort();
    ~TreeSort();
    void sort(std::vector<int>& vec);

    friend class Sorting;
};


#endif //TREE_SORT_TREE_SORT_H
