#include "array.h"
#include "stack.h"
#include <iostream>
#include <conio.h>

// Тесты: 5 21 7 23 19 3 11 17 2 29 13 31 37 41 43 47 5 59 61 67 77 88 99 111 5 21 7 23 19 3 11 17 2 29 13 31 37 41 43 47 5 59 99 111 5 21 7 23 19 3 11 17 2 29 61 67 77 88 99 111
using namespace std;

int MIN_RUN = 64;

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
int gallopMode (type array[], type key, int base, int length, int startI)
{
    int lastShift = 0;
    int shift = 1;

    if (key > array[base + startI])
    {
        int maxOffset = length - startI;
        while (shift < maxOffset && key > array[base + startI + shift])
        {
            lastShift = shift;
            shift = (shift << 1) + 1;
        }
        if (shift > maxOffset) shift = maxOffset;

        lastShift += startI;
        shift += startI;
    }
    else
    {
        int maxOffset = startI + 1;
        while (shift < maxOffset && key <= array[base + startI - shift])
        {
            lastShift = shift;
            shift = (shift << 1) + 1;
        }
        if (shift > maxOffset) shift = maxOffset;

        int temp = lastShift;
        lastShift = startI - shift;
        shift = startI - temp;
    }

    lastShift++;

    while (lastShift < shift)
    {
        int mid = lastShift + ((shift - lastShift) >> 1);
        if (key > array[base + mid])
        {
            lastShift = mid + 1;
        }
        else
        {
            shift = mid;
        }
    }
    return shift;
}

template<typename type>
void merge(type array[], int left, int mid, int right)
{
    int len1 = mid - left + 1;
    int len2 = right - mid;

    type* leftArr = new type[len1];
    for (int i = 0; i < len1; i++)
    {
        leftArr[i] = array[left + i];
    }

    int i = 0, j = mid + 1, k = left;
    int gallopConst = 7;

    while (i < len1 && j <= right)
    {
        int gallopCount = 0;

        while (i < len1 && j <= right && leftArr[i] <= array[j])
        {
            array[k++] = leftArr[i++];
            gallopCount++;
            if (gallopCount >= gallopConst)
            {
                int next = gallopMode(leftArr, array[j], i, len1 - i, 0);
                while (i < next)
                {
                    array[k++] = leftArr[i++];
                }
                break;
            }
        }
        gallopCount = 0;
        while (j <= right && i < len1 && array[j] < leftArr[i])
        {
            array[k++] = array[j++];
            gallopCount++;
            if (gallopCount >= gallopConst)
            {
                int next = gallopMode(array, leftArr[i], j, right - j + 1, 0);
                while (j < next)
                {
                    array[k++] = array[j++];
                }
                break;
            }
        }
    }

    while (i < len1)
    {
        array[k++] = leftArr[i++];
    }
    delete[] leftArr;
}

int getMinRunLength(int n)
{
    int  r = 0;
    while (n >= MIN_RUN)
    {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

template <typename type>
void reverse(type* first, type* last)
{
    type* left = first;
    type* right = last - 1;

    while (left < right)
    {

        type temp = *left;
        *left = *right;
        *right = temp;

        left++;
        right--;
    }
}

template<typename type>
int findRun (type array[], int left, int right)
{
    if (left >= right) return left;

    int i = left + 1;
    if (array[i] >= array[i - 1])
    {
        while (i <= right && array[i] >= array[i - 1]) i++;
    }
    else
    {
        while (i <= right && array[i] < array[i - 1]) i++;
        reverse(array + left, array + i);
    }
    return i - 1;
}

template<typename type>
void mergeInvariants(type array[], Stack<Run>& runs)
{
    while (runs.size() > 1)
    {
        Run z = runs.top(); runs.pop();
        Run y = runs.top(); runs.pop();

        if (runs.size() > 0)
        {
            Run x = runs.top();


            if (z.length > y.length + x.length || y.length > x.length)
            {
                runs.push(y);
                runs.push(z);
                break;
            }

            if (x.length <= z.length)
            {
                merge(array, x.start, x.start + x.length - 1, y.start + y.length - 1);
                runs.pop();
                runs.push(Run(x.start, x.length + y.length));
                runs.push(z);
            }
            else
            {
                merge(array, y.start, y.start + y.length - 1, z.start + z.length - 1);
                runs.push(Run(y.start, y.length + z.length));
            }
        }
        else
        {
            if (y.length > z.length)
            {
                runs.push(y);
                runs.push(z);
                break;
            }
            else
            {
                merge(array, y.start, y.start + y.length - 1, z.start + z.length - 1);
                runs.push(Run(y.start, y.length + z.length));
            }
        }
    }
}

template<typename type>
void timSort(type array[], int n)
{
    if (n < 2) return;

    int minRun = getMinRunLength(n);

    Stack<Run> runs;
    int i = 0;


    while (i < n)
    {

        int runEnd = findRun(array, i, n - 1);
        int runLength = runEnd - i + 1;

        if (runLength < minRun) {
            int newEnd = min(i + minRun - 1, n - 1);
            insertSort(array, i, newEnd);
            runEnd = newEnd;
            runLength = runEnd - i + 1;
        }

        runs.push(Run(i, runLength));

        mergeInvariants(array, runs);
        i = runEnd + 1;
    }

    while (runs.size() > 1)
    {
        Run z = runs.top(); runs.pop();
        Run y = runs.top(); runs.pop();

        merge(array, y.start, y.start + y.length - 1, z.start + z.length - 1);
        runs.push(Run(y.start, y.length + z.length));
    }
}


void mainMenu(int str)
{
    system("cls");
    printf("%s1 - Work with array\n", str == 1 ? " => " : "    ");
    printf("%s2 - Timsort\n", str == 2 ? " => " : "    ");
    printf("%s0 - Exit\n", str == 0 ? " => " : "    ");
}

void arrMenu(int str)
{
    printf("%s 1 - Create and fill\n", str == 1 ? " => " : "    ");
    printf("%s 2 - Print elements\n", str == 2 ? " => " : "    ");
    printf("%s 3 - Insert element\n", str == 3 ? " => " : "    ");
    printf("%s 4 - Delete element by index\n", str == 4 ? " => " : "    ");
    printf("%s 5 - Get an element by index\n", str == 5 ? " => " : "    ");
    printf("%s 6 - Swap elements\n", str == 6 ? " => " : "    ");
    printf("%s 0 - Exit\n", str == 0 ? " => " : "    ");
}

void timMenu(int str)
{
    printf("%s1 - Sort the array\n", str == 1 ? " => " : "    ");
    printf("%s0 - Exit\n", str == 0 ? " => " : "    ");
}

int main()
{


    int flag = 0, flag2 = 0, flag3(0);
    int current_selection_global = 1;
    int menu_items_count_global = 3;
    int current_selection_arr = 1;
    int menu_items_count_arr = 7;
    int current_selection_tim = 1;
    int menu_items_count_tim = 2;
    int choice, choice2, choice3;
    auto* array = new Array<int>();

    int value;
    int index1, index2;
    int* element;
    short index;

    while (flag == 0)
    {
        mainMenu(current_selection_global);
        choice = _getch();
        if (choice >= '0' && choice <= '2') current_selection_global = choice - '0';
        if (choice == 224)
        {
            choice = _getch();
            switch (choice)
            {
            case 72:
                system("cls");
                current_selection_global = (current_selection_global - 1 + menu_items_count_global) % menu_items_count_global;
                break;
            case 80:
                system("cls");
                current_selection_global = (current_selection_global + 1) % menu_items_count_global;
                break;
            }
        }
        if (choice == 13)
        {
            switch (current_selection_global)
            {
            case 1:
                system("cls");
                while (flag2 == 0)
                {
                    system("cls");
                    cout << "Current array: ";
                    array->print();
                    cout << endl;
                    arrMenu(current_selection_arr);
                    choice2 = _getch();
                    if (choice2 >= '0' && choice2 <= '6') current_selection_arr = choice2 - '0';
                    if (choice2 == 224)
                    {
                        choice2 = _getch();
                        switch (choice2)
                        {
                        case 72:
                            current_selection_arr = (current_selection_arr - 1 + menu_items_count_arr) % menu_items_count_arr;
                            break;
                        case 80:
                            current_selection_arr = (current_selection_arr + 1) % menu_items_count_arr;
                            break;
                        }
                    }
                    if (choice2 == 13)
                    {

                        switch (current_selection_arr)
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
                while (flag3 == 0)
                {
                    system("cls");
                    cout << "Current array: ";
                    array->print();
                    cout << endl;
                    timMenu(current_selection_tim);
                    choice3 = _getch();
                    if (choice3 >= '0' && choice3 <= '1') current_selection_tim = choice3 - '0';
                    if (choice3 == 224)
                    {
                        choice3 = _getch();
                        switch (choice3)
                        {
                        case 72:
                            current_selection_tim = (current_selection_tim - 1 + menu_items_count_tim) % menu_items_count_tim;
                            break;
                        case 80:
                            current_selection_tim = (current_selection_tim + 1) % menu_items_count_tim;
                            break;
                        }
                    }
                    if (choice3 == 13)
                    {
                        switch (current_selection_tim)
                        {
                            case 1:
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
                            case 2:
                                cout << "Press any key to continue...";
                                _getch();
                                break;
                            case 0:
                                flag3 = 1;
                                break;
                            default:
                                break;
                        }
                    }
                }
                flag3 = 0;
                break;
            case 0:
                system("cls");
                return 0;
                break;

            }
        }
    }
}