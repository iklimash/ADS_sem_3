#pragma once

#include <iostream>

using namespace std;

template<typename type> class Array
{
public:

	type* array;
	int currSize = 0;
	int capacity = 0;

	Array();
	Array(int size);
	~Array();

	/*bool empty();*/

	void pushBack(const type& value);
	void print();
	void insertElement(short index, type value);
	void deleteElement(short index);
	void swap(short index1, short index2);
	type *getElement(short index);
	void insertionSort();
};

template <typename type> Array<type>::Array()
{
	currSize = 0;
	capacity = 5;
	array = new type[capacity];
}

template <typename type> Array<type>::Array(int size)
{
	if (size < 0)
	{
		size = 5;
	}
	capacity = size;
	array = new type[capacity];
}

template <typename type> Array<type>::~Array()
{
	delete[] array;
	array = nullptr;
}

//template <typename type> bool Array<type>::empty()
//{
//	if (currSize == 0) return true;
//	return false;
//}

template <typename type> void Array<type>::pushBack(const type& value)
{
	if (currSize >= capacity)
	{
		size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
		type* newArray = new type[newCapacity];

		for (size_t i = 0; i < currSize; ++i)
		{
			newArray[i] = array[i];
		}

		delete[] array;
		array = newArray;
		capacity = newCapacity;
	}
	array[currSize] = value;
	++currSize;

}

template <typename type> void Array<type>::print()
{
	if (currSize == 0) return;
	cout << '[';
	for (int i = 0; i < currSize; i++)
	{
		cout << array[i];
		if (i < currSize - 1) {
			cout << ", ";
		}
	}
	cout << ']' << endl;
}

template <typename type> void Array<type>::insertElement(short index, type value)
{
	if (index < 0 || index > currSize) return;
	
	if (index == currSize)
	{
		this->pushBack(value);
		return;
	}
	if (currSize + 1 >= capacity) {
		capacity *= 2;
	}
	type* temp = new type[capacity];
	if (index > currSize) {
		for (int i = 0; i < currSize; i++) {
			temp[i] = array[i];
		}
		for (int i = currSize; i < index; i++) {
			temp[i] = 0;
		}
		temp[index] = value;
	}
	else {
		for (int i = 0; i < index; i++) {
			temp[i] = array[i];
		}
		*(temp + index) = value;
		for (int i = index + 1; i <= currSize; i++) {
			temp[i] = array[i - 1];
		}
	}
	if (index > currSize) {
		currSize = index + 1;
	}
	else {
		currSize++;
	}
	delete[] array;
	array = temp;
}

template <typename type> void Array<type>::deleteElement(short index)
{
	if (index < 0 || index > currSize) return;
	capacity--;
	type* temp = new type[capacity];
	for (size_t i = 0; i < index; ++i)
	{
		*(temp + i) = *(array + i);
	}
	for (size_t i = index + 1; i < currSize; ++i)
	{
		*(temp + i - 1) = *(array + i);
	}
	currSize--;
	delete[] array;
	array = temp;
}

template <typename type> type* Array<type>::getElement(short index)
{
	if (index < 0 || index >= currSize) return nullptr;
	return array + index;
}
template <typename type> void Array<type>::swap(short index1, short index2)
{
	if (index1 < 0 || index1 >= currSize || index2 < 0 || index2 >= currSize) {
		return;
	}

	if (index1 != index2) {
		type temp = array[index1];     
		array[index1] = array[index2];  
		array[index2] = temp;        
	}
}

template <typename type> void Array<type>::insertionSort()
{
	for (size_t i = 0; i < currSize; ++i)
	{
		type key = array[i];
		int j = i - 1;
		while (j >= 0 && array[j] > key)
		{
			array[j + 1] = array[j];
			j--;
		}
		array[j + 1] = key;
	}
}