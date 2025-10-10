#pragma once

#include <string>
#include <iostream>

using namespace std;

class SortStation
{
public:

	string getString();
	
	int priority(char c);

	double operation(double a, double b, char c);

	bool calculateValue(string& output);

    string ReversPolishnotation(std::string& inputString, bool& flag);

};

template<typename type> 
class StackKnot{
public:
	type values;
	int priority;
	StackKnot* next;
	StackKnot(type& inputValues, int inputPriority);
};

template<typename type> 
StackKnot<type>::StackKnot(type& inputValues, int inputPriority) {

	values = inputValues;
	priority = inputPriority;
	next = nullptr;
}

template<typename type> 
class Stack {
public:
    StackKnot<type> *head;
    StackKnot<type> *tail;

    Stack();
    ~Stack();

    void pushFront(type inputValues, int inputPriority);
    void popFront();

    
};



template<typename type> 
Stack<type>::Stack() : head(nullptr), tail(nullptr) {}


template<typename type>
Stack<type>::~Stack()
{
    while (head != nullptr) popFront();
}



template<typename type>
void Stack<type>::pushFront(type inputValues, int inputPriority) 
{
    auto* node = new StackKnot<type>(inputValues, inputPriority);
    node->next = head;
    head = node;
    if (tail == nullptr) tail = node;
}


template<typename type> 
void Stack<type>::popFront() 
{
    if (head == nullptr) return;
    if (head == tail) {
        delete tail;
        head = tail = nullptr;
        return;
    }
    StackKnot<type>* node = head;
    head = node->next;
    delete node;
}

