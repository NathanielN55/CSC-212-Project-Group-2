# CSC-212-Project-Group-2
# Left-Leaning Red-Black Binary Search Trees

### Compilation Instructions

Make sure you have the files llrbtree.cpp, llrbtree.h, and main.cpp downloaded from this repository and stored in the same file. To compile, open your terminal, navigate to the directory where you stored the downloaded code files, and run the following command:

`g++ -std=c++11 llrbtree.cpp main.cpp -o llrbtree`

This will create your executable file `llrbtree`. 

### Runtime Instructions

Before you run the program, make sure you have your input text file in the same folder as your executable file `llrbtree`. To run the program, open your terminal, navigate to the directory where you stored the executable file and the input file, and run the following command:

`./llrbtree <in_file_name> <mode> <txt_out_file_name> <dot_out_file_name>`

`<in_file_name>` is the name of the input .txt file. Make sure to include the .txt extension when you type this command line argument into the terminal. `<txt_out_file_name>` is the name of the output text file, and `<dot_out_file_name>` is the name of the output dot file. Do not include an extension in these command line arguments; the program will generate the extension automatically. `<mode>` indicates the mode of the .txt output as follows:

- 1: Prints out a preorder traversal of the tree
- 2: Prints out an inorder traversal of the tree
- 3: Prints out both a preorder and an inorder traversal of the tree
- 4: Prints out a postorder traversal of the tree
- 5: Prints out both a preorder and a postorder traversal of the tree
- 6: Prints out both an inorder and a postorder traversal of the tree
- 7: Prints out a preorder, inorder, and postorder traversal of the tree

An example of a properly formatted run command is as follows:

`./llrbtree tree_input.txt 1 tree_output`

