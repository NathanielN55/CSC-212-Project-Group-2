//
// Created by Jack on 6/30/2023.
//

#ifndef LAB5_LLRBTREE_H
#define LAB5_LLRBTREE_H

#pragma once

#include <iostream>
#include <ostream>
using namespace std;

#ifndef MAX
#define MAX(a,b) ((a > b) ? a : b)
#endif

class LLRBNode {
private:
    int data;
    bool red;
    LLRBNode* left;
    LLRBNode* right;
    void flip_color();
public:
    LLRBNode();
    LLRBNode(int data);
    ~LLRBNode();

    friend class LLRBTree;
};

class LLRBTree {
private:
    LLRBNode* root;
    LLRBNode* insert(int data, LLRBNode* root);
    LLRBNode* remove(int data, LLRBNode* root);
    LLRBNode* find_ios(LLRBNode* root, bool &disconnect);
    LLRBNode* rotate_left(LLRBNode* root);
    LLRBNode* rotate_right(LLRBNode* root);
    int height(LLRBNode* root);

    void flip_color(LLRBNode* root);
    void preorder(LLRBNode* root, ostream &os);
    void inorder(LLRBNode* root, ostream &os);
    void postorder(LLRBNode* root, ostream &os);

    void destroy(LLRBNode* root);
    bool search(int data, LLRBNode* root);
    bool redNode(LLRBNode* node);

public:
    LLRBTree();
    ~LLRBTree();

    void insert(int data);
    void remove(int data);
    int height();

    void preorder(ostream &os = cout);
    void inorder(ostream &os = cout);
    void postorder(ostream &os = cout);

    bool search(int data);
    void clear();
};

#endif //LAB5_LLRBTREE_H
