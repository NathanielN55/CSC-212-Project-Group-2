#include "llrbtree.h"
#include <fstream>
#include <string>
#include <sstream>

void print_tree(LLRBTree* tree, int mode, std::ofstream& os);

int main(int argc, char *argv[]){
    ifstream infile(argv[1]);
    int mode = stoi(argv[2]);
    string txtname(argv[3]);
    string dotname(argv[3]);
    txtname += ".txt";
    dotname += ".dot";

    ofstream txtfile(txtname);

    LLRBTree tree;

    string line;

    getline(infile, line);
    stringstream ss(line);

    int num;
    while (ss >> num) {
        tree.insert(num);

    }

    print_tree(&tree, mode, txtfile);
    txtfile << "Tree Height: " << tree.height() << endl;
    txtfile.close();


    ofstream dotfile(dotname);

    tree.generateDotFile(dotfile);

    dotfile.close();
    
}

/*
 * pre = 1
 * in = 2
 * post = 4
 * pre+in = 3
 * pre+post = 5
 * in+post = 6
 * pre+in+post = 7
 */
void print_tree(LLRBTree* tree, int mode, std::ofstream& os){
    if(mode == 1 || mode == 3 || mode == 5 || mode == 7){
        tree->preorder(os);
    }
    if(mode == 2 || mode == 3 || mode == 6 || mode == 7){
        tree->inorder(os);
    }
    if(mode == 4 || mode == 5 || mode == 6 || mode == 7){
        tree->postorder(os);
    }
}
