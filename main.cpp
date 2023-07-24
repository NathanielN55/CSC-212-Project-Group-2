#include "llrbtree.h"
#include <fstream>
#include <string>
#include <sstream>

void print_tree(LLRBTree* tree, int mode, std::ofstream& os);

int main(int argc, char *argv[]){
    // Input file name
    ifstream infile(argv[1]);
    // Mode number
    int mode = stoi(argv[2]);
    // Names of the output files
    string txtname(argv[3]);
    string dotname(argv[3]);
    txtname += ".txt";
    dotname += ".dot";

    // Open the text file output stream
    ofstream txtfile(txtname);

    // Create a new tree
    LLRBTree tree;

    string line;

    getline(infile, line);
    stringstream ss(line);

    // Insert each number in the input file into the tree
    int num;
    while (ss >> num) {
        tree.insert(num);

    }

    // Print the necessary tree info to the text file
    print_tree(&tree, mode, txtfile);
    txtfile << "Tree Height: " << tree.height() << endl;
    // Close the text file output stream
    txtfile.close();

    // Open the dot file output stream
    ofstream dotfile(dotname);
    // Generate the dot file 
    tree.generateDotFile(dotfile);
    // Close the dot file
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
