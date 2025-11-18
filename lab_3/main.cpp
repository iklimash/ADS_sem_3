#include "binaryTree.h"
#include "AVLTree.h"
#include <iostream>


using namespace std;

int main()
{
    int choice;
    BinaryTree<int>* currentTree = nullptr;
    while (true)
    {
        cout << "\n1 - Work with BinaryTree\n";
        cout << "2 - Work with AVLTree\n";
        cout << "0 - Exit\n> ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                BinaryTree<int> treeFromFile;
                treeFromFile.loadFromFile("tree.txt");
                cout << "Tree structure from file:" << endl;
                cout << treeFromFile.treeToString(treeFromFile.getRoot()) << endl;

                cout << "Pre-order: ";
                treeFromFile.depthFirstPreOrder(treeFromFile.getRoot());
                cout << endl;
                cout << "In-order: ";
                treeFromFile.depthFirstInOrder(treeFromFile.getRoot());
                cout << endl;
                cout << "Post-order: ";
                treeFromFile.depthFirstPostOrder(treeFromFile.getRoot());
                cout << endl;
                break;
            }
            case 2:
            {
                AVLTree<int> tree;
                cout << "Insert element: ";
                int values[] = {10, 20, 30, 40, 50, 25};
                for (int i = 0; i < 6; i++)
                {
                    cout << values[i] << " ";
                    tree.insert(values[i]);
                }
                cout << endl << endl;

                cout << "Content:" << endl;
                tree.printTree();
                cout << endl;

                cout << "Breadth-first traversal: ";
                tree.breadthFirstTraversal();

                cout << "Pre-order: ";
                tree.preOrderTraversal();

                cout << "In-order: ";
                tree.inOrderTraversal();

                cout << "Post-order: ";
                tree.postOrderTraversal();
                cout << endl;

                cout << "Search element:" << std::endl;
                cout << "25: " << (tree.search(25) ? "Search" : "not search") << endl;
                cout << "35: " << (tree.search(35) ? "Search" : "not search") << endl;
                cout << endl;

                cout << "Delete 25:" << endl;
                tree.remove(25);
                tree.printTree();
                cout << endl;

                cout << "Delete 30:" << endl;
                tree.remove(30);
                tree.printTree();

                break;
            }
            case 0:
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    }
}