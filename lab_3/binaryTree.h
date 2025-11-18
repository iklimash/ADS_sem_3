#ifndef LAB_3_BINARYTREE_H
#define LAB_3_BINARYTREE_H

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
using namespace std;

template <typename type>
struct Node
{
    type data;
    Node<type> *left;
    Node<type> *right;

    Node(const type& value) : data(value), left(nullptr), right(nullptr) {}
    string toString() const
    {
        return to_string(data);
    }
};

template <typename type>
class BinaryTree
{
public:

    BinaryTree() : root(nullptr) {}

    ~BinaryTree()
    {
        clearSupport(root);
    }

    // Pre-order: корень -> левое -> правое
    static void depthFirstPreOrder(const Node<type>* node)
    {
        if (!node) return;
        cout << node->data << " ";
        depthFirstPreOrder(node->left);
        depthFirstPreOrder(node->right);
    }

    // In-order: левое -> корень -> правое
    static void depthFirstInOrder(const Node<type>* node)
    {
        if (!node) return;
        depthFirstInOrder(node->left);
        cout << node->data << " ";
        depthFirstInOrder(node->right);
    }

    // Post-order: левое -> правое -> корень
    static void depthFirstPostOrder(const Node<type>* node)
    {
        if (!node) return;
        depthFirstPostOrder(node->left);
        depthFirstPostOrder(node->right);
        cout << node->data << " ";
    }
    // Добавьте этот метод в public секцию класса BinaryTree
    void printTree() const
    {
        if (!root)
        {
            cout << "Tree is empty" << endl;
            return;
        }

        struct QueueItem
        {
            Node<type>* node;
            QueueItem* next;
            QueueItem(Node<type>* n) : node(n), next(nullptr) {}
        };

        class SimpleQueue
        {
            QueueItem* front;
            QueueItem* rear;
        public:
            SimpleQueue() : front(nullptr), rear(nullptr) {}
            ~SimpleQueue() { clear(); }

            void enqueue(Node<type>* node)
            {
                QueueItem* newItem = new QueueItem(node);
                if (!rear) front = rear = newItem;
                else {
                    rear->next = newItem;
                    rear = newItem;
                }
            }

            Node<type>* dequeue()
            {
                if (!front) return nullptr;
                QueueItem* temp = front;
                Node<type>* result = front->node;
                front = front->next;
                if (!front) rear = nullptr;
                delete temp;
                return result;
            }

            bool isEmpty() const { return front == nullptr; }

            int size() const
            {
                int count = 0;
                QueueItem* current = front;
                while (current) {
                    count++;
                    current = current->next;
                }
                return count;
            }

            void clear()
            {
                while (!isEmpty()) dequeue();
            }
        };

        SimpleQueue q;
        q.enqueue(root);


        while (!q.isEmpty())
        {
            int levelSize = q.size();

            for (int i = 0; i < levelSize; i++)
            {
                Node<type>* current = q.dequeue();

                cout << current->data;

                if (current->left || current->right) {
                    cout << " [";
                    if (current->left) {
                        cout << "L:" << current->left->data;
                    } else {
                        cout << "L:-";
                    }
                    cout << " ";
                    if (current->right) {
                        cout << "R:" << current->right->data;
                    } else {
                        cout << "R:-";
                    }
                    cout << "]";
                }

                cout << "   ";

                if (current->left) q.enqueue(current->left);
                if (current->right) q.enqueue(current->right);
            }
            cout << endl;
        }
    }
    
    string treeToString(Node<type>* root)
    {
        string result;
        output(root, "", true, &result);
        return result;
    }

    void parseFromString(const string& str)
    {
        clear();
        size_t pos = 0;
        root = parseSubtree(str, pos);

        if (pos < str.length())
        {
            throw invalid_argument("Invalid bracket notation format");
        }
    }

    void loadFromFile(const string& filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            throw runtime_error("Cannot open file: " + filename);
        }

        string line;
        getline(file, line);
        file.close();

        parseFromString(line);
    }

    bool isEmpty() const
    {
        return root == nullptr;
    }

    Node<type> *getRoot() const
    {
        return root;
    }

    void clear()
    {
        clearSupport(root);
        root = nullptr;
    }

private:

    Node<type>* root;

    Node<type>* parseSubtree(const string& str, size_t& pos)
    {
        skipWhitespace(str, pos);

        if (pos >= str.length() || str[pos] != '(')
        {
            throw invalid_argument("Expected '(' at position " + to_string(pos));
        }
        pos++;

        skipWhitespace(str, pos);

        type value = readValue(str, pos);
        Node<type>* node = new Node<type>(value);

        skipWhitespace(str, pos);

        if (pos < str.length() && str[pos] == '(')
        {
            node->left = parseSubtree(str, pos);
            skipWhitespace(str, pos);
        }

        if (pos < str.length() && str[pos] == '(')
        {
            node->right = parseSubtree(str, pos);
            skipWhitespace(str, pos);
        }

        if (pos >= str.length() || str[pos] != ')')
        {
            throw invalid_argument("Expected ')' at position " + to_string(pos));
        }
        pos++;

        return node;
    }

    void skipWhitespace(const string& str, size_t& pos)
    {
        while (pos < str.length() && isspace(str[pos]))
        {
            pos++;
        }
    }


    type readValue(const string& str, size_t& pos)
    {
        size_t start = pos;
        while (pos < str.length() && (isdigit(str[pos]) || str[pos] == '-'))
        {
            pos++;
        }

        if (start == pos)
        {
            throw invalid_argument("Expected number at position " + to_string(pos));
        }

        string valueStr = str.substr(start, pos - start);
        return stoi(valueStr);
    }

    void clearSupport(Node<type>* node)
    {
        if (!node) return;
        clearSupport(node->left);
        clearSupport(node->right);
        delete node;
    }

};

#endif //LAB_3_BINARYTREE_H