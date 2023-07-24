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

// Class of nodes for the tree
class LLRBNode {
private:
    // Holds the relevant data
    int data;
    // Determines if this node is red (true) or black (false)
    bool red;
    // Pointers to this node's left and right child nodes
    LLRBNode* left;
    LLRBNode* right;
    // Private setter for changing color of the node
    void flip_color();
public:
    LLRBNode();
    LLRBNode(int data);
    ~LLRBNode();

    friend class LLRBTree;
};

class LLRBTree {
private:
    // Tree's root node, from which all others are accessed via pointers
    LLRBNode* root;

    // Collection of methods for manipulating data, defined privately
    // so that they can be called within public versions of these functions
    // without allowing manual manipulation of the tree
    LLRBNode* insert(int data, LLRBNode* root);
    LLRBNode* remove(int data, LLRBNode* root);
    LLRBNode* find_ios(LLRBNode* root, bool &disconnect);

    // Important functions for rotating the tree when necessary
    LLRBNode* rotate_left(LLRBNode* root);
    LLRBNode* rotate_right(LLRBNode* root);
    int height(LLRBNode* root);
    void flip_color(LLRBNode* root);

    // Functions for printing the tree in various named orders
    void preorder(LLRBNode* root, ostream &os);
    void inorder(LLRBNode* root, ostream &os);
    void postorder(LLRBNode* root, ostream &os);
    void generateDotFile(LLRBNode *root, std::ostream &os);

    void destroy(LLRBNode* root);
    bool search(int data, LLRBNode* root);
    bool redNode(LLRBNode* node);

public:
    LLRBTree();
    ~LLRBTree();
    // Functions for manipulating the tree which call the
    // private functions in order to maintain the tree's integrity
    void insert(int data);
    void remove(int data);
    int height();

    void preorder(ostream &os = cout);
    void inorder(ostream &os = cout);
    void postorder(ostream &os = cout);

    void generateDotFile(ostream &os = cout);

    bool search(int data);
    void clear();
};

#endif //LAB5_LLRBTREE_H
