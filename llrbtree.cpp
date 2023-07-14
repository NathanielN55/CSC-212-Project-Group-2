//
// Created by Jack on 6/30/2023.
//
#include "llrbtree.h"

/*
 * Node Class Functions
 */

LLRBNode::LLRBNode() {
    this->data = 0;
    this->red = true;
    this->left = nullptr;
    this->right = nullptr;
}

LLRBNode::LLRBNode(int data) {
    this->data = data;
    this->red = true;
    this->left = nullptr;
    this->right = nullptr;
}

LLRBNode::~LLRBNode() {

}

/*
 * Tree Class Functions - Private
 */

LLRBNode* LLRBTree::insert(int data, LLRBNode* root) {
    if (!root) {
        return new LLRBNode(data);
    }
    if (data < root->data) {
        root->left = insert(data, root->left);
    } else {
        root->right = insert(data, root->right);
    }

    if ((!redNode(root->left)) && redNode(root->right)){
        root = rotate_left(root);
        root->red = root->left->red;
        root->left->red = true;
    }

    if (redNode(root->left) && redNode((root->left)->left)){
        root = rotate_right(root);
        root->red = root->right->red;
        root->right->red = true;
    }

    if (redNode(root->left) && redNode(root->right)){
        flip_color(root);
        flip_color(root->left);
        flip_color(root->right);
    }

    return root;
}

LLRBNode* LLRBTree::remove(int data, LLRBNode* root) {
    if (!root) {
        return nullptr;
    }
    if (data == root->data) {
        LLRBNode* temp;
        if (root->left == root->right) {
            delete root; return nullptr;
        }
        if (!root->left != !root->right) {
            root->left ? temp = root->left: temp = root->left;
            delete root; return temp;
        }
        temp = root->right;
        while (temp->left) {
            temp = temp->left;
        }
        root->data = temp->data;
        root->right = remove(temp->data, root->right);
        return root;
    }
    if (data < root->data) {
        root->left = remove(data, root->left);
    } else {
        root->right = remove(data, root->right);
    }
    return root;
}

LLRBNode* LLRBTree::find_ios(LLRBNode *root, bool &disconnect) {
    if (!root->left) {
        disconnect = true; return root;
    }
    LLRBNode* temp = find_ios (root->left, disconnect);

    if (disconnect) {
        root->left = nullptr;
        disconnect = false;
    }
    return temp;
}

LLRBNode* LLRBTree::rotate_left(LLRBNode* root) {
    LLRBNode* temp = root->right;
    root->right = root->right->left;
    temp->left = root;
    return temp;
}

LLRBNode* LLRBTree::rotate_right(LLRBNode* root) {
    LLRBNode* temp = root->left;
    root->left = root->left->right;
    temp->right = root;
    return temp;
}

int LLRBTree::height(LLRBNode* root) {
    if (!root) {
        return -1;
    }
    int left = height(root->left);
    int right = height(root->right);

    return (left > right ? left + 1 : right + 1);
}

void LLRBTree::flip_color(LLRBNode *root) {
    if (root == nullptr) {
        return;
    }

    if (root->red) {
        root->red = false;
    } else {
        root->red = true;
    }

    return;
}

void LLRBTree::preorder(LLRBNode* root, ostream &os) {
    if (!root) { return; }

    os << root->data << ":" << root->red << " ";
    this->preorder(root->left, os);
    this->preorder(root->right, os);

    return;
}

void LLRBTree::inorder(LLRBNode* root, ostream &os) {
    if (!root) { return; }

    this->inorder(root->left, os);
    os << root->data << ":" << root->red << " ";
    this->inorder(root->right, os);

    return;
}

void LLRBTree::postorder(LLRBNode *root, std::ostream &os) {
    if (!root) { return; }

    this->postorder(root->left, os);
    this->postorder(root->right, os);
    os << root->data << ":" << root->red << " ";

    return;
}

void LLRBTree::destroy(LLRBNode *root) {
    if (!root) { return; }

    this->destroy(root->left);
    this->destroy(root->right);
    delete root->left;
    delete root->right;
}

bool LLRBTree::search(int data, LLRBNode* root) {
    if (!root) { return false; }

    if (data == root->data) { return true; }

    if (data < root->data) {
        return this->search(data, root->left);
    } else {
        return this->search(data, root->right);
    }
}

bool LLRBTree::redNode(LLRBNode *node) {
    if (node == nullptr) {
        return false;
    }
    if (node->red) {
        return true;
    } else {
        return false;
    }
}

/*
 * Tree Class Functions - Public
 */

LLRBTree::LLRBTree() {
    this->root = nullptr;
}

LLRBTree::~LLRBTree() {
    this->destroy(this->root);
}

void LLRBTree::insert(int data) {
    this->root = this->insert(data, this->root);
    this->root->red = false;
}

void LLRBTree::remove(int data) {
    this->root = this->remove(data, this->root);
}

int LLRBTree::height() {
    return this->height(this->root);
}

void LLRBTree::preorder(std::ostream &os) {
    this->preorder(this->root, os);
    os << "\n";
}

void LLRBTree::inorder(std::ostream &os) {
    this->inorder(this->root, os);
    os << "\n";
}

void LLRBTree::postorder(std::ostream &os) {
    this->postorder(this->root, os);
    os << "\n";
}

bool LLRBTree::search(int data) {
    return this->search(data, this->root);
}

void LLRBTree::clear() {
    this->destroy(this->root);
    this->root = nullptr;
}
