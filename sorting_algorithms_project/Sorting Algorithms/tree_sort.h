//
// Created by asalm on 11/3/2023.
//

#ifndef TREE_SORT_TREE_SORT_H
#define TREE_SORT_TREE_SORT_H

#include <iostream>
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
    void inorder(Node* n, int arr[], int &i);
    Node* insert(Node* n, int key);
    void destroy(Node* n);


public:
    TreeSort();
    ~TreeSort();
    void sort(int arr[], int n);
};


#endif //TREE_SORT_TREE_SORT_H
