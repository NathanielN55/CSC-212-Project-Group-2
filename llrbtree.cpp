#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
//
// Created by Jack on 6/30/2023.
//
#include "llrbtree.h"

/*
 * Node Class Functions
 */

LLRBNode::LLRBNode() {
    // Default constructor creates a red node with 0 as
    // the data and no child nodes
    this->data = 0;
    this->count = 0;
    this->red = true;
    this->left = nullptr;
    this->right = nullptr;
}

LLRBNode::LLRBNode(int data) {
    // Same as default constructor except data is set
    // to parameter passed in
    this->data = data;
    this->count = 1;
    this->red = true;
    this->left = nullptr;
    this->right = nullptr;
}

LLRBNode::~LLRBNode() = default;

/*
 * Tree Class Functions - Private
 */

LLRBNode* LLRBTree::insert(int data, LLRBNode* root) {
    // If there is no root (pointer to this node is null),
    // create the root (node at this position) and return it
    if (!root) {
        return new LLRBNode(data);
    }
    // If the data is less than the current node's,
    // move left down the tree and call this function recursively,
    // otherwise move right down the tree and call the function
    // recursively, moving down the tree until the above if statement runs
    if (data < root->data) {
        root->left = insert(data, root->left);
    } else if (data > root->data) {
        root->right = insert(data, root->right);
    } else {
        root->count++;
    }

    // Next three 'if blocks' are about maintaining the three big
    // rules of LLRB trees:
    // First, if a node's left child is black and right child
    // is red, rotate left.
    if ((!redNode(root->left)) && redNode(root->right)){
        root = rotate_left(root);
        root->red = root->left->red;
        root->left->red = true;
    }
    // Second, if a node's left child and left grandchild are red,
    // rotate right.
    if (redNode(root->left) && redNode((root->left)->left)){
        root = rotate_right(root);
        root->red = root->right->red;
        root->right->red = true;
    }
    // Third, if both of a node's child nodes are red, invert the
    // colors of all nodes.
    if (redNode(root->left) && redNode(root->right)){
        flip_color(root);
        flip_color(root->left);
        flip_color(root->right);
    }
    // The inserted node is returned
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

// The next two functions define behavior for left and right rotations:
// To rotate left, you assign the current node's right to a temporary variable,
// then set the current node's right child to be the former right child's left.
// Then the former right child's left, becomes the current node. This way the
// Former right is now the top of the triangle, the former top is now the left,
// and the former right's left child has moved to the former top's right.
LLRBNode* LLRBTree::rotate_left(LLRBNode* root) {
    LLRBNode* temp = root->right;
    root->right = root->right->left;
    temp->left = root;
    return temp;
}

// To rotate right, the same happens in reverse, where the current node's left
// is assigned to a temporary container, then the current node's left becomes the
// former left child's right. Everything moves the same as in rotate left, but
// in opposite directions, and again the new 'top' of the triangle is returned as
// the root of a fixed subtree.
LLRBNode* LLRBTree::rotate_right(LLRBNode* root) {
    LLRBNode* temp = root->left;
    root->left = root->left->right;
    temp->right = root;
    return temp;
}

// Returns an error value (-1) for empty trees, otherwise returns the result of
// a recursive chain which increments by one at each level of the tree
int LLRBTree::height(LLRBNode* root) {
    if (!root) {
        return -1;
    }
    int left = height(root->left);
    int right = height(root->right);

    return (left > right ? left + 1 : right + 1);
}

// Breaks out of the function if the tree is empty, otherwise takes the 
// current red-ness of the current node and changes it
void LLRBTree::flip_color(LLRBNode *root) {
    if (root == nullptr) {
        return;
    }

    if (root->red) {
        root->red = false;
    } else {
        root->red = true;
    }
}

// Breaks out of the function in case of empty tree, otherwise it
// prints the current node's info, then left subtree's preorder call,
// then right subtrees preorder call, in appropriate preorder direction.
void LLRBTree::preorder(LLRBNode* root, ostream &os) {
    if (!root) { return; }

    os << root->data << ":" << root->red << " ";
    this->preorder(root->left, os);
    this->preorder(root->right, os);
}

// Same as preorder, but prints left subtree's inorder call,
// then the current node, then the right subtree's inorder call.
void LLRBTree::inorder(LLRBNode* root, ostream &os) {
    if (!root) { return; }

    this->inorder(root->left, os);
    os << root->data << ":" << root->red << " ";
    this->inorder(root->right, os);
}

// Just like the other two, again with order altered slightly
// so that left subtree's postorder info prints, then right subtree,
// and last in line is the current node.
void LLRBTree::postorder(LLRBNode *root, std::ostream &os) {
    if (!root) { return; }

    this->postorder(root->left, os);
    this->postorder(root->right, os);
    os << root->data << ":" << root->red << " ";
}

// Recursively moves down the tree calling destroy, then as
// each call to destroy resolves, the current node's left and
// right children are destroyed, and we move back up the tree.
void LLRBTree::destroy(LLRBNode *root) {
    if (!root) { return; }

    this->destroy(root->left);
    this->destroy(root->right);
    delete root->left;
    delete root->right;
}

// Returns false if we've entered a non-existent node (such as
// an empty tree or end of a branch) and return true if the
// current node matches our search. Uses recursive calls after
// to move down the tree in appropriate direction based in the data input
bool LLRBTree::search(int data, LLRBNode* root) {
    if (!root) { return false; }

    if (data == root->data) { return true; }

    if (data < root->data) {
        return this->search(data, root->left);
    } else {
        return this->search(data, root->right);
    }
}

// Returns red-ness of the selected node, returns false for null pointers
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
 * Tree Class Functions - Public:
    Many of these call the private version of the function,
    these are compartmentalized in order to keep properties of
    the tree private and not directly modifiable.
 */

// Default constructor creates a tree with no nodes
LLRBTree::LLRBTree() {
    this->_root = nullptr;
}

// Destructor calls destroy to remove all nodes recursively
LLRBTree::~LLRBTree() {
    this->destroy(this->_root);
}

// Calls private method, and also ensures that root is black
// once the recursion unwinds
void LLRBTree::insert(int data) {
    this->_root = this->insert(data, this->_root);
    this->_root->red = false;
}

// Calls private method
void LLRBTree::remove(int data) {
    this->_root = this->remove(data, this->_root);
}

// Calls private method
int LLRBTree::height() {
    return this->height(this->_root);
}

// Calls private method
void LLRBTree::preorder(std::ostream &os) {
    this->preorder(this->_root, os);
    os << "\n";
}

// Calls private method
void LLRBTree::inorder(std::ostream &os) {
    this->inorder(this->_root, os);
    os << "\n";
}

// Calls private method
void LLRBTree::postorder(std::ostream &os) {
    this->postorder(this->_root, os);
    os << "\n";
}

void LLRBTree::generateDotFile(LLRBNode *root, std::ostream &os){
    // If we have reached a null pointer, recursively go back
    if (!root) { return; }

    // If we are at the root of the tree, start with the header of the dot file
    if (root == this->_root) {
        os << "digraph G {" << std::endl << std::endl;
    }

    // Print out node/path data for the left side of the current node
    if (root->left != nullptr){
        os << '\t' << root->data << " -> " << root->left->data << " [color=" << '"';
        if (root->left->red){
            os << "red";
        }
        else {
            os << "black";
        }
        os << '"' << "];" << std::endl; 
    }

    // Print out node/path data for the right side of the current node
    if (root->right != nullptr){
        os << '\t' << root->data << " -> " << root->right->data << " [color=" << '"';
        if (root->right->red){
            os << "red";
        }
        else {
            os << "black";
        }
        os << '"' << "];" << std::endl; 
    }

    // Recursively move to the left node and follow the same pattern
    this->generateDotFile(root->left, os);
    // Recursively move to the right node and follow the same pattern
    this->generateDotFile(root->right, os);

    // If we have recursively returned to the root node, add the closing bracket at the end
    if (root == this->_root) {
        os << std::endl << "}" << std::endl;
    }


}

// Calls a private method
bool LLRBTree::search(int data) {
    return this->search(data, this->_root);
}

// Calls destroy to empty the tree without deleting the structure entirely,
// like the destructor would do
void LLRBTree::clear() {
    this->destroy(this->_root);
    this->_root = nullptr;
}

#pragma clang diagnostic pop