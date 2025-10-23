#include "array.h"
#include <iostream>
#include <conio.h>

using namespace std;

int MIN_RUN = 32;

template<typename type>
void insertSort(type array[], int left, int right)
{
    for (int i = left + 1; i <= right; i++)
    {
        type key = array[i];
        int j = i - 1;
        while (j >= left && array[j] > key)
        {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
    }
}

template<typename type>
void merge(type array[], int left, int mid, int right)
{
    int len1 = mid - left + 1;
    int len2 = right - mid;
    int* arrLeft = new type[len1];
    int* arrRight = new type[len2];
    for (int i = 0; i < len1; i++)
        arrLeft[i] = array[left + i];
    for (int i = 0; i < len2; i++)
        arrRight[i] = array[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < len1 && j < len2)
    {
        if (arrLeft[i] <= arrRight[j])
        {
            array[k] = arrLeft[i];
            i++;
        }
        else
        {
            array[k] = arrRight[j];
            j++;
        }
        k++;
    }

    while (i < len1)
    {
        array[k] = arrLeft[i];
        i++;
        k++;
    }
    while (j < len2)
    {
        array[k] = arrRight[j];
        j++;
        k++;
    }

    delete[] arrLeft;
    delete[] arrRight;
}

int getMinRunLength(int n)
{
    int  r = 0;
    while (n >= MIN_RUN)
    {
        r |= n & 1;      // Запоминаем младший бит
        n >>= 1;         // Делим n пополам
    }
    return n + r;
}

template<typename type>
void timSort(type array[], int n)
{
    int minRun = getMinRunLength(n);
    for (int i = 0; i < n; i += minRun)
    {
        insertSort(array, i, min((i + minRun - 1), (n - 1)));
    }
    for (int size = minRun; size < n; size *= 2 )
    {
        for (int left = 0; left < n; left += 2 * size)
        {
            int mid = left + size - 1;
            int right = min((left + 2 * size - 1), (n - 1));
            merge(array, left, mid, right);
        }
    }
}

void mainMenu(int str)
{
    system("cls");
    printf("%s1 - Work with array\n", str == 1 ? " => " : "    ");
    printf("%s2 - Timsort\n", str == 2 ? " => " : "    ");
    printf("%s0 - Exit\n", str == 3 ? " => " : "    ");
}

void arrMenu(int str)
{
    system("cls");
    printf("%s 1 - Create and fill\n", str == 1 ? " => " : "    ");
    printf("%s 2 - Print elements\n", str == 2 ? " => " : "    ");
    printf("%s 3 - Insert element\n", str == 3 ? " => " : "    ");
    printf("%s 4 - Delete element by index\n", str == 4 ? " => " : "    ");
    printf("%s 5 - Get an element by index\n", str == 5 ? " => " : "    ");
    printf("%s 6 - Swap elements\n", str == 6 ? " => " : "    ");
    printf("%s 0 - Exit\n", str == 0 ? " => " : "    ");
}

int main()
{

    int str = 1, flag = 0;
    int str2 = 1, flag2 = 0;
    int choice, choice2;
    auto* array = new Array<int>();

    int value;
    int index1, index2;
    int* element;
    short index;

    while (flag == 0) {
        mainMenu(str);
        choice = _getch();
        if (choice >= '1' && choice <= '2') str = choice - '0';
        if (choice == 224) {
            choice = _getch();
            switch (choice) {
            case 72:
                str = (str - 1 + 2) % 3 + 1;
                break;
            case 80:
                str = (str - 1 + 1) % 3 + 1;
                break;
            }
        }
        if (choice == 13)
        {
            switch (str)
            {
            case 1:
                system("cls");
                while (flag2 == 0) {
                    system("cls");
                    array->print();
                    arrMenu(str2);
                    choice2 = _getch();
                    if (choice2 >= '1' && choice2 <= '6') str2 = choice2 - '0';
                    if (choice2 == 224) {
                        choice2 = _getch();
                        switch (choice2) {
                        case 72:
                            str2 = (str2 - 1) % 7;
                            break;
                        case 80:
                            str2 = (str2 + 1) % 7;
                            break;
                        }
                    }
                    if (choice2 == 13)
                    {

                        switch (str2)
                        {
                            case 1:
                                cout << "Input numbers please: ";
                                delete array;
                                array = new Array<int>();
                                cin.clear();
                                while (cin >> value)
                                {
                                    array->pushBack(value);
                                    if (cin.peek() == '\n')
                                    {
                                        break;
                                    }
                                }
                                cout << "Your current array: ";
                                array->print();
                                cout << "Press any key to continue...";
                                _getch();
                                break;
                            case 2:

                                cout << "Array contents: ";
                                array->print();
                                cout << "Press any key to continue...";
                                _getch();
                                break;
                            case 3:
                                cout << "Input index and value please: ";
                                cin >> index; cin >> value;
                                array->insertElement(index, value);

                                cout << "Array contents: ";
                                array->print();
                                cout << "Press any key to continue...";
                                _getch();
                                break;
                            case 4:
                                cout << "Input index please: ";
                                cin >> index;
                                array->deleteElement(index);

                                cout << "Array contents: ";
                                array->print();
                                cout << "Press any key to continue...";
                                _getch();
                                break;
                            case 5:
                                cout << "Input index please: ";
                                cin >> index;
                                element = array->getElement(index);

                                if (element != nullptr) {
                                    cout << "Element at index " << index << ": " << *element << endl;
                                }
                                else {
                                    cout << "Invalid index!" << endl;
                                }
                                cout << "Array contents: ";
                                array->print();
                                cout << "Press any key to continue...";
                                _getch();
                                break;
                            case 6:
                                cout << "Input index1 and index2 please: ";
                                cin >> index1; cin >> index2;
                                array->swap(index1, index2);
                                system("cls");
                                cout << "Array contents: ";
                                array->print();
                                cout << "Press any key to continue...";
                                _getch();
                                break;
                            case 0:
                                flag2 = 1;
                                break;
                            default:
                                break;
                        }
                    }
                }
                flag2 = 0;
                break;
            case 2:
                system("cls");
                if (array->getSize() > 0)
                {
                    cout << "Original array: ";
                    array->print();

                    timSort(array->getData(), array->getSize());

                    cout << "Sorted array: ";
                    array->print();
                }
                else
                {
                    cout << "Array is empty!" << endl;
                }
                cout << "Press any key to continue...";
                _getch();
                break;
            case 3:
                system("cls");
                return 0;
                break;

            }
        }
    }
}