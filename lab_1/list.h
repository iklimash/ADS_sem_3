#pragma once

#include <iostream>

using namespace std;

template<typename type>
class ListKnot
{
public:
	type values;
	ListKnot* prev;
	ListKnot* next;
	explicit ListKnot(type inputValues);
};

template<typename type>
class List
{
	short len;
	ListKnot<type> *head;
	ListKnot<type> *tail;
public:

	List();
	~List();

	short length();
	void deleteKnot(short index);
	ListKnot<type>* getKnot(short index);
	void insert(short index, int value);

	void pushFront(type values);
	void pushBack(type values);
	void popBack();
	void popFront();

	void swap(short index1, short index2);
	void print();

};

template<typename type>
ListKnot<type>::ListKnot(type inputValues)
{
	values = inputValues;
	next = prev = nullptr;
}

template<typename type>
List<type>::List()
{
	len = 0;
	head = tail = nullptr;
}

template<typename type>
List<type>::~List()
{
	while (head != nullptr) popBack();
}

template<typename type>
short List<type>::length()
{
	return len;
}

template<typename type>
void List<type>::pushFront(type values) {

	ListKnot<type>* knot = new ListKnot<type>(values);
	knot->next = head;
	if (head != nullptr) {
		head->prev = knot;
	}
	if (tail == nullptr) {
		tail = knot;
	}
	head = knot;
	len++;
}

template<typename type>
void List<type>::pushBack(type values)
{
	ListKnot<type>* knot = new ListKnot<type>(values);
	knot->prev = tail;
	if (tail != nullptr)
	{
		tail->next = knot;
	}
	if (head == nullptr)
	{
		head = knot;
	}
	tail = knot;
	++len;
}

template<typename type>
void List<type>::popFront() {

	if (head == nullptr) return;
	ListKnot<type>* knot = head->next;
	if (knot != nullptr) {
		knot->prev = nullptr;
	}
	else
		tail = nullptr;
	delete head;
	head = knot;
	--len;
}

template<typename type>
void List<type>::popBack()
{
	if (tail == nullptr) return;

	ListKnot<type> *knot = tail->prev;
	if (knot != nullptr)
	{
		knot->next = nullptr;
	}
	else
	{
		head = nullptr;
	}
	delete tail;
	tail = knot;
	--len;

}
template<typename type>
void List<type>::deleteKnot(short index) {

	ListKnot<type>* knot = getKnot(index);
	if (knot == nullptr) {
		return;
	}
	if (knot->prev == nullptr) {
		popFront();
		return;
	}
	if (knot->next == nullptr) {
		popBack();
		return;
	}
	ListKnot<type>* left = knot->prev;
	ListKnot<type>* right = knot->next;
	left->next = right;
	right->prev = left;
	delete knot;
	--len;
}

template<typename type>
ListKnot<type>* List<type>::getKnot(short index)
{
	ListKnot<type>* knot = head;
	int n = 0;

	while (n != index)
	{
		if (knot == nullptr) return nullptr;
		knot = knot->next;
		++n;
	}
	return knot;
}

template<typename type>
void List<type>::insert(short index, int value)
{
	if (index < 0 || index > len) return;

	ListKnot<type>* currKnot = getKnot(index);
	if (currKnot == nullptr) {
		pushBack(value);
		return;
	}

	ListKnot<type>* prevCurrKnot = currKnot->prev;
	if (prevCurrKnot == nullptr) {
		pushFront(value);
		return;
	}

	ListKnot<type>* newKnot = new ListKnot<type>(value);
	newKnot->prev = prevCurrKnot;
	newKnot->next = currKnot;
	prevCurrKnot->next = newKnot;
	currKnot->prev = newKnot;
	++len;

}

template<typename type>
void List<type>::swap(short index1, short index2)
{

	if (index1 == index2) return;

	if (index1 > index2) {
		swap(index1, index2);
	}

	ListKnot<type>* node1 = getKnot(index1);
	ListKnot<type>* node2 = getKnot(index2);

	if (node1 == nullptr || node2 == nullptr) return;


	ListKnot<type>* prev1 = node1->prev;
	ListKnot<type>* next1 = node1->next;
	ListKnot<type>* prev2 = node2->prev;
	ListKnot<type>* next2 = node2->next;


	if (node1->next == node2) {

		node1->next = next2;
		node1->prev = node2;
		node2->next = node1;
		node2->prev = prev1;

		if (prev1) prev1->next = node2;
		else head = node2;

		if (next2) next2->prev = node1;
		else tail = node1;
	}
	else {

		node1->next = next2;
		node1->prev = prev2;
		node2->next = next1;
		node2->prev = prev1;


		if (prev1) prev1->next = node2;
		else head = node2;

		if (next1) next1->prev = node2;
		else tail = node2;

		if (prev2) prev2->next = node1;
		else head = node1;

		if (next2) next2->prev = node1;
		else tail = node1;
	}
}
template<typename type>
void List<type>::print()
{
	cout << '[';
	ListKnot<type>* current = head;
	while (current != nullptr)
	{
		cout << current->values;
		if (current->next != nullptr)
		{
			cout << ", ";
		}
		current = current->next;
	}
	cout << ']' << endl;
}