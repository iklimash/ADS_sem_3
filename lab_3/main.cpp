#include "binaryTree.h"
#include "AVLTree.h"
#include <iostream>



using namespace std;
void menuAVLtree()
{
    cout << "1 - Insert element" << endl;
    cout << "2 - Delete element" << endl;
    cout << "3 - Search element" << endl;
    cout << "4 - Breadth-first traversal" << endl;
    cout << "5 - Depth-first traversal" << endl;
    cout << "6 - Print" << endl;
    cout << "0 - Back to main menu\n> ";
}

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
                treeFromFile.printTree();

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
                int choiceTree;
                int deleteValue;
                AVLTree<int> AVLtree;
                while (true)
                {
                    menuAVLtree();
                    cin >> choiceTree;
                    switch (choiceTree)
                    {
                        case 1:
                        {
                            cout << "Insert element: ";

                            cin.ignore();
                            string input;
                            getline(cin, input);
                            stringstream ss(input);
                            int values;

                            while (ss >> values)
                            {
                                AVLtree.insert(values);
                            }
                            cout << "Current tree structure:" << endl;
                            AVLtree.printTree();
                            break;
                        }
                        case 2:
                        {
                            cout << "Input element: ";
                            cin >> deleteValue;

                            AVLtree.remove(deleteValue);
                            AVLtree.printTree();
                            cout << endl;
                            break;
                        }
                        case 3:
                        {
                            cout << "Search element: ";
                            cin.ignore();
                            string input;
                            getline(cin, input);
                            stringstream ss(input);
                            int value;
                            while (ss >> value)
                            {
                                cout << (AVLtree.search(value) ? "Search" : "not search");
                            }
                            cout << endl;
                            break;
                        }
                        case 4:
                        {
                            cout << "Breadth-first traversal: ";
                            AVLtree.breadthFirstTraversal();
                            break;
                        }
                        case 5:
                        {
                            cout << "Pre-order: ";
                            AVLtree.preOrderTraversal();
                            cout << "In-order: ";
                            AVLtree.inOrderTraversal();
                            cout << "Post-order: ";
                            AVLtree.postOrderTraversal();
                            cout << endl;
                            break;
                        }
                        case 6:
                        {
                            cout << "Current tree structure:" << endl;
                            AVLtree.printTree();
                            break;
                        }
                        case 0:
                        {break;}
                        default:
                            cout << "Invalid choice! Please try again." << endl;
                            break;
                    }
                    if (choiceTree == 0)
                    {
                        break;
                    }
                }
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