# CSC-212-Project-Group-2
# Left-Leaning Red-Black Binary Search Trees

### Compilation Instructions

Make sure you have the files llrbtree.cpp, llrbtree.h, and main.cpp downloaded and stored in the same file. To compile, open your terminal, navigate to the directory where you stored the downloaded code files, and run the following command:

`g++ -std=c++11 llrbtree.cpp main.cpp -o llrbtree`

This will create your executable file `llrbtree`. 

### Runtime Instructions

Before you run the program, make sure you have your input text file in the same folder as your executable file `llrbtree`. To run the program, open your terminal, navigate to the directory where you stored the executable file and the input file, and run the following command:

`./llrbtree <mode> <out_file_name>`

<out_file_name> is the name of the two output files, not including the extension (do not include an extension in the command line argument; the program will generate two output files with the same name, one with the .txt extension and one with the .dot extension). <mode> indicates the mode of the .txt output as follows:

- 1: Prints out a preorder traversal of the tree
- 2: Prints out an inorder traversal of the tree
- 3: Prints out both a preorder and an inorder traversal of the tree
- 4: Prints out a postorder traversal of the tree
- 5: Prints out both a preorder and a postorder traversal of the tree
- 6: Prints out both an inorder and a postorder traversal of the tree
- 7: Prints out a preorder, inorder, and postorder traversal of the tree

