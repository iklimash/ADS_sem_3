#include "station.h"
#include <cmath>

using namespace std;

string SortStation::getString()
{
    string input;
    getline(cin, input);
    return input;
}

int SortStation::priority(char c) {
    switch (c) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    case '(':
    case ')':
        return 0;
    case ' ':
        return 10;
    default:
        if (isdigit(c)) return -1;
        else if (c >= 'a' && c < 'z' || c >= 'A' && c <= 'Z') return -1;
        else return -2;
    }
}

string SortStation::ReversPolishnotation(string& inputString, bool& flag)
{
    auto* stack = new Stack<string>();
    string output;
    string  curr;
    int len = inputString.length();
    for (int i = 0; i < len; i++)
    {
        if (curr == "sin" || curr == "cos")
        {
            stack->pushFront(curr, 4);
            curr.clear();
        }
        switch (priority(inputString[i]))
        {
        case -1:
            curr.push_back(inputString[i]);
            break;
        case 0:
            if (!curr.empty())
            {
                output += curr + " ";
                curr.clear();
            }
            if (inputString[i] == '(')
            {
                stack->pushFront("(", 0);
            }
            else
            {
                while (stack->head != nullptr && stack->head->values != "(")
                {
                    output += stack->head->values + " ";
                    stack->popFront();
                }
                if (stack->head == nullptr)
                {
                    flag = true;
                    delete stack;
                    return " ";
                }
                stack->popFront();

                if (stack->head != nullptr &&
                    (stack->head->values == "sin" || stack->head->values == "cos"))
                {
                    output += stack->head->values + " ";
                    stack->popFront();
                }
            }
            break;
        case 1:
        case 2:
            if (!curr.empty()) {
                output += curr + " ";
                curr.clear();
            }
            if (stack->head == nullptr || stack->head->priority < priority(inputString[i])) {
                stack->pushFront(inputString.substr(i, 1), priority(inputString[i]));
            } else {
                while (stack->head != nullptr && stack->head->priority >= priority(inputString[i])) {
                    output += stack->head->values;
                    output.push_back(' ');
                    stack->popFront();
                }
                stack->pushFront(inputString.substr(i, 1), priority(inputString[i]));
            }
            break;
        case 3:
                // Обработка оператора ^
                if (!curr.empty())
                {
                    output += curr + " ";
                    curr.clear();
                }
                if (stack->head == nullptr || stack->head->priority < priority(inputString[i]))
                {
                    stack->pushFront(inputString.substr(i, 1), priority(inputString[i]));
                }
                else {
                    while (stack->head != nullptr && stack->head->priority > priority(inputString[i]))
                    {
                        output += stack->head->values;
                        output.push_back(' ');
                        stack->popFront();
                    }
                    stack->pushFront(inputString.substr(i, 1), priority(inputString[i]));
                }
                break;
        case 10:
            if (!curr.empty())
            {
                output += curr + " ";
                curr.clear();
            }
            break;
        }
    }
    if (!curr.empty())
    {
        output += curr + " ";
        curr.clear();
    }
    while (stack->head != nullptr) {
        output += stack->head->values;
        output.push_back(' ');
        stack->popFront();
    }
    delete stack;
    if (!output.empty() && output.back() == ' ')
        output.pop_back();
    return output;
}

bool SortStation::calculateValue(string& output)
{
    auto* stack = new Stack<string>();
    string curr;
    double result = 0;
    double variable = 0;
    int len = output.length();

    for (int i = 0; i < len; i++)
    {
        if (output[i] != ' ')
        {
            switch (priority(output[i]))
            {
            case -1:
                curr.push_back(output[i]);
                break;
            case 0:
                return false;
            case 1:
            case 2:
            case 3:
                if (stack->head == stack->tail)
                {
                    cout << "\nError! Small amount operands\n";
                    return false;
                }
                if (!isdigit(stack->head->values[0]))
                {
                    variable = 1;
                }
                else variable = stod(stack->head->values);
                result = variable;
                stack->popFront();
                if (output[i] == '/' && result == 0)
                {
                    cout << "\nDon't divide by zero\n";
                    return false;
                }
                if (!isdigit(stack->head->values[0]))
                {
                    variable = 1;
                }
                else variable = stod(stack->head->values);
                result = operation(variable, result, output[i]);
                stack->popFront();
                curr = to_string(result);
                stack->pushFront(curr, -1);
                curr = "";
                break;
            default:
                cout << "\nError";
                return false;
            }
        }
        else {
            if (!curr.empty())
            {
                if (curr == "sin")
                {
                    if (stack->head == nullptr)
                    {
                        cout << "\nError! Small amount operands\n";
                        return false;
                    }
                    if (!isdigit(stack->head->values[0]))
                    {
                        variable = 1;
                    }
                    else variable = stod(stack->head->values);
                    result = sin(variable);
                    stack->popFront();
                    curr = to_string(result);
                    stack->pushFront(curr, -1);
                }
                else if (curr == "cos")
                {
                    if (stack->head == nullptr)
                    {
                        cout << "\nError! Small amount operands\n";
                        return false;
                    }
                    if (!isdigit(stack->head->values[0]))
                    {
                        variable = 0;
                    }
                    else variable = stod(stack->head->values);
                    result = cos(variable);
                    stack->popFront();
                    curr = to_string(result);
                    stack->pushFront(curr, -1);
                }
                else
                {
                    stack->pushFront(curr, -1);
                }
                curr = "";
            }
        }
    }
    if (stack->head != stack->tail)
    {
        cout << "\nError! Small amount operands\n";
        return false;
    }

    return true;
}


double SortStation::operation(double a, double b, char c) {
    switch (c) {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    case '^':
        return pow(a, b);
    default:
        return 0;
    }
}