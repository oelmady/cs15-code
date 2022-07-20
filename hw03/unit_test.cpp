#include <iostream>

#include "BinarySearchTree.h"

using namespace std;

void print_tree_details(BinarySearchTree &bst)
{
    bst.print_tree();
    cout << "\n";
    cout << "min: "         << bst.find_min()    << "\n";
    cout << "max: "         << bst.find_max()    << "\n";
    cout << "nodes: "       << bst.node_count()  << "\n";
    cout << "count total: " << bst.count_total() << "\n";
    cout << "tree height: " << bst.tree_height() << "\n";
    cout << "\n";
}

int main()
{
    BinarySearchTree bst;
    // int values[] = {4, 1,2,3};
    int values[]  = {2, 1, 3, 0, 5};
    int numValues = sizeof(values) / sizeof(int);


    for (int i = 0; i < numValues; i++) {
            bst.insert(values[i]);
    }
    BinarySearchTree bst_copy_1;
    bst_copy_1 = bst;

    bst.print_tree();

    cout << "Removing 1 from original tree:\n";
    bst.remove(1);
    print_tree_details(bst);
    cout << "restoring original tree" << endl;
    bst = bst_copy_1;

    cout << "Removing 0 from original tree:\n";
    bst.remove(0);
    print_tree_details(bst);
    cout << "restoring original tree" << endl;
    bst = bst_copy_1;

    cout << "Removing 2 from original tree:\n";
    bst.remove(2);
    print_tree_details(bst);
    cout << "restoring original tree" << endl;
    bst = bst_copy_1;

    return 0;
}