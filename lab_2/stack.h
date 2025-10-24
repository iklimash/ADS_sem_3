//
// Created by iklim on 24.10.2025.
//

#ifndef LAB_2_STACK_H
#define LAB_2_STACK_H

struct Run {
    int start;
    int length;

    Run(int s = 0, int l = 0) : start(s), length(l) {}
};

template<typename type>
class StackKnot {
public:
    type data;
    StackKnot* next;

    StackKnot(const type& value) : data(value), next(nullptr) {}
};

template<typename type>
class Stack
{
private:
    StackKnot<type>* topKnot;
    int stackSize;

public:

    Stack() : topKnot(nullptr), stackSize(0) {}
    ~Stack();
    bool empty() const;
    void pop();
    void push(const type& value);
    int size() const;
    type& top();
};

template<typename type>
Stack<type>::~Stack()
{
    while (!empty())
    {
        pop();
    }
}

template<typename type>
bool Stack<type>::empty() const
{
    return topKnot == nullptr;
}

template<typename type>
void Stack<type>::pop()
{
    if (empty())
    {
        return;
    }
    StackKnot<type>* temp = topKnot;
    topKnot = topKnot->next;
    delete temp;
    stackSize--;
}

template<typename type>
int Stack<type>::size() const
{
    return stackSize;
}

template<typename type>
void Stack<type>::push(const type& value)
{
    StackKnot<type>* newKnot= new StackKnot<type>(value);
    newKnot->next = topKnot;
    topKnot = newKnot;
    stackSize++;
}

template<typename type>
type& Stack<type>::top()
{
    if (empty())
    {
        throw runtime_error("Stack is empty");
    }
    return topKnot->data;
}
















#endif //LAB_2_STACK_H