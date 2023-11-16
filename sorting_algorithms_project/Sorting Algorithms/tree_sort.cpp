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

void TreeSort::inorder(Node *n, std::vector<int> &vec, int &i) {
    if(n) {
        inorder(n->left, vec, i);
        vec[i++] = n->data;
        inorder(n->right, vec, i);
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

void TreeSort::sort(std::vector<int>& vec) {
    root = insert(root, vec[0]);

    for(int i = 1; i < vec.size(); i++) {
        root = insert(root, vec[i]);
    }

    int i = 0;
    inorder(root, vec, i);
}