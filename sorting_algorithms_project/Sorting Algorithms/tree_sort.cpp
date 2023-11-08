//
// Created by asalm on 11/3/2023.
//

#include "tree_sort.h"

Node::Node(int d) {
    data = d;
    left = nullptr;
    right = nullptr;
}

Node::~Node(){}

TreeSort::TreeSort() {
    root = nullptr;
}

TreeSort::~TreeSort() {
    destroy(root);
}

void TreeSort::destroy(Node *n) {
    if(!n) {
        return;
    }

    destroy(n->left);
    destroy(n->right);
    delete n;
}

void TreeSort::inorder(Node *n, int arr[], int &i) {
    if(n) {
        inorder(n->left, arr, i);
        arr[i++] = n->data;
        inorder(n->right, arr, i);
    }
}

Node* TreeSort::insert(Node *n, int key) {
    if(!n) {
        return new Node(key);
    }

    if (key < n->data) {
        n->left = insert(n->left, key);
    } else {
        n->right = insert(n->right, key);
    }
    return n;
}

void TreeSort::sort(int *arr, int n) {
    root = insert(root, arr[0]);

    for(int i = 1; i < n; i++) {
        root = insert(root, arr[i]);
    }

    int i = 0;
    inorder(root, arr, i);
}