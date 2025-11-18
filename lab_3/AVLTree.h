#ifndef LAB_3_AVLTREE_H
#define LAB_3_AVLTREE_H

#include <iostream>

using namespace std;

template<typename type>
class AVLTree
{
    public:

    AVLTree() : root(nullptr) {}

    AVLTree(const AVLTree& other)
    {
        root = copy(other.root);
    }

    AVLTree& operator=(const AVLTree& other)
    {
        if (this != &other) {
            clear();
            root = copy(other.root);
        }
        return *this;
    }

    ~AVLTree()
    {
        clear();
    }

    void insert(const type& value)
    {
        root = insert(root, value);
    }

    void remove(const type& value)
    {
        root = remove(root, value);
    }

    bool search(const type& value) const
    {
        return search(root, value);
    }

    // Обход в ширину (корень -> лево -> право)
    void breadthFirstTraversal() const
    {
        if (!root) return;

        Queue q;
        q.enqueue(root);

        while (!q.isEmpty())
        {
            Node* current = q.dequeue();

            cout << current->data << " ";

            if (current->left)
            {
                q.enqueue(current->left);
            }
            if (current->right)
            {
                q.enqueue(current->right);
            }
        }
        cout << endl;
    }

    // Прямой обход (pre-order) корень -> левое -> правое
    void preOrderTraversal() const {
        if (!root) return;

        Stack s;
        s.push(root);

        while (!s.isEmpty())
        {
            Node* current = s.pop();

            cout << current->data << " ";


            if (current->right)
            {
                s.push(current->right);
            }
            if (current->left)
            {
                s.push(current->left);
            }
        }
        cout << endl;
    }

    // Симметричный обход (in-order) левое -> корень -> правое
    void inOrderTraversal() const
    {
        Stack s;
        Node* current = root;

        while (current || !s.isEmpty())
            {

            while (current)
            {
                s.push(current);
                current = current->left;
            }

            current = s.pop();
            cout << current->data << " ";


            current = current->right;
        }
        cout << endl;
    }

    // Обратный обход (post-order) левое -> правое -> корень
    void postOrderTraversal() const
    {
        if (!root) return;

        Stack s1, s2;
        s1.push(root);

        while (!s1.isEmpty())
        {
            Node* current = s1.pop();
            s2.push(current);

            if (current->left)
            {
                s1.push(current->left);
            }
            if (current->right)
            {
                s1.push(current->right);
            }
        }

        while (!s2.isEmpty())
        {
            cout << s2.pop()->data << " ";
        }
        cout << endl;
    }

    void clear()
    {
        clear(root);
        root = nullptr;
    }

    bool isEmpty() const
    {
        return root == nullptr;
    }

    void printTree() const
    {
        if (!root)
        {
            cout << "Tree is empty" << endl;
            return;
        }

        Queue q;
        q.enqueue(root);

        while (!q.isEmpty())
        {
            int levelSize = 0;
            QueueNode* current = q.getFront();
            while (current) {
                levelSize++;
                current = current->next;
            }

            for (int i = 0; i < levelSize; i++)
            {
                Node* current = q.dequeue();
                cout << current->data << "(" << current->height << ") ";

                if (current->left)
                {
                    q.enqueue(current->left);
                }
                if (current->right)
                {
                    q.enqueue(current->right);
                }
            }
            cout << endl;
        }
    }

private:
    struct Node
    {
        type data;
        Node* left;
        Node* right;
        int height;

        Node(const type& value) : data(value), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    int getHeight(Node* node)
    {
        return node ? node->height : 0;
    }

    int max(int a, int b)
    {
        return (a > b) ? a : b;
    }

    int getBalance(Node* node)
    {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    void updateHeight(Node* node)
    {
        if (node)
        {
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        }
    }

    Node* rotateRight(Node* y)
    {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* rotateLeft(Node* x)
    {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* balanceNode(Node* node)
    {
        if (!node) return node;

        updateHeight(node);
        int balance = getBalance(node);


        if (balance > 1 && getBalance(node->left) >= 0)
        {
            return rotateRight(node);
        }

        if (balance < -1 && getBalance(node->right) <= 0)
        {
            return rotateLeft(node);
        }

        if (balance > 1 && getBalance(node->left) < 0)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }


        if (balance < -1 && getBalance(node->right) > 0)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node* insert(Node* node, const type& value)
    {
        if (!node)
        {
            return new Node(value);
        }

        if (value < node->data)
        {
            node->left = insert(node->left, value);
        }
        else if (value > node->data)
        {
            node->right = insert(node->right, value);
        }
        else
        {
            return node;
        }
        return balanceNode(node);
    }

    Node* findMin(Node* node)
    {
        while (node && node->left)
        {
            node = node->left;
        }
        return node;
    }

    Node* remove(Node* node, const type& value)
    {
        if (!node) return node;

        if (value < node->data)
        {
            node->left = remove(node->left, value);
        }
        else if (value > node->data)
        {
            node->right = remove(node->right, value);
        }
        else
        {

            if (!node->left || !node->right)
            {
                Node* temp = node->left ? node->left : node->right;

                if (!temp)
                {
                    temp = node;
                    node = nullptr;
                }
                else
                {
                    *node = *temp;
                }
                delete temp;
            }
            else
            {
                Node* temp = findMin(node->right);
                node->data = temp->data;
                node->right = remove(node->right, temp->data);
            }
        }

        if (!node) return node;

        return balanceNode(node);
    }

    bool search(Node* node, const type& value) const
    {
        while (node)
        {
            if (value == node->data)
            {
                return true;
            }
            else if (value < node->data)
            {
                node = node->left;
            }
            else
            {
                node = node->right;
            }
        }
        return false;
    }

    void clear(Node* node)
    {
        if (node)
        {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    Node* copy(Node* node)
    {
        if (!node) return nullptr;

        Node* newNode = new Node(node->data);
        newNode->left = copy(node->left);
        newNode->right = copy(node->right);
        newNode->height = node->height;

        return newNode;
    }

    struct StackNode
    {
        Node* treeNode;
        StackNode* next;

        StackNode(Node* node) : treeNode(node), next(nullptr) {}
    };

    class Stack
    {
    private:
        StackNode* top;

    public:

        Stack() : top(nullptr) {}

        ~Stack()
        {
            while (!isEmpty())
            {
                pop();
            }
        }

        void push(Node* node)
        {
            StackNode* newNode = new StackNode(node);
            newNode->next = top;
            top = newNode;
        }

        Node* pop()
        {
            if (!top) return nullptr;

            StackNode* temp = top;
            Node* result = top->treeNode;
            top = top->next;
            delete temp;
            return result;
        }

        Node* peek() const
        {
            return top ? top->treeNode : nullptr;
        }

        bool isEmpty() const
        {
            return top == nullptr;
        }
    };

    struct QueueNode
    {
        Node* treeNode;
        QueueNode* next;

        QueueNode(Node* node) : treeNode(node), next(nullptr) {}
    };

    class Queue
    {
    private:
        QueueNode* front;
        QueueNode* rear;

    public:

        Queue() : front(nullptr), rear(nullptr) {}

        ~Queue()
        {
            while (!isEmpty())
            {
                dequeue();
            }
        }

        void enqueue(Node* node)
        {
            QueueNode* newNode = new QueueNode(node);

            if (!rear)
            {
                front = rear = newNode;
            } else
            {
                rear->next = newNode;
                rear = newNode;
            }
        }

        Node* dequeue()
        {
            if (!front) return nullptr;

            QueueNode* temp = front;
            Node* result = front->treeNode;
            front = front->next;

            if (!front) {
                rear = nullptr;
            }

            delete temp;
            return result;
        }

        bool isEmpty() const
        {
            return front == nullptr;
        }
        QueueNode* getFront() const
        {
            return front;
        }
    };
};

#endif //LAB_3_AVLTREE_H