#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Graph.h"

// Разбивает строку на слова
int SplitTokens(const string& line, string tokens[], int maxTokens)
{
    istringstream iss(line);
    string temp;
    int count = 0;

    while (iss >> temp && count < maxTokens)
    {
        tokens[count++] = temp;
    }

    return count;
}

// Читаем матрицу смежности и строим граф
Graph* ParseAdjacencyMatrix(const string& filePath)
{
    ifstream in(filePath);
    if (!in.is_open())
    {
        cout << "Error: cannot open file " << filePath << "\n";
        return nullptr;
    }

    string line;

    // Читаем первую строку — имена вершин
    if (!getline(in, line))
    {
        cout << "Error: file is empty\n";
        return nullptr;
    }

    string tokens[MAX_VERTICES];
    int numVertices = SplitTokens(line, tokens, MAX_VERTICES);

    if (numVertices <= 0)
    {
        cout << "Error: no vertex names found\n";
        return nullptr;
    }

    Graph* g = new Graph(numVertices);

    for (int i = 0; i < numVertices; ++i) g->SetVertexName(i, tokens[i]);

    // Читаем строки матрицы
    int row = 0;
    while (getline(in, line) && row < numVertices)
    {
        istringstream iss(line);
        int weight;
        int col = 0;

        while (iss >> weight && col < numVertices)
        {
            if (weight > 0 && row <= col) g->AddEdgeByIndex(row, col, weight); // диогонали учитываем A - A
            col++;
        }
        row++;
    }
    return g;
}

void printMenu()
{
    cout << "Main menu:\n";
    cout << "1. Initialization Graph\n";
    cout << "2. Graph traversal\n";
    cout << "3. Find Min Spanning Tree\n";
    cout << "4. Print Graph\n";
    cout << "0. Exit\n";
}

void application()
{
    Graph* graph = nullptr;
    int choice = 0;

    printMenu();

    while (true)
    {
        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input, try again\n";
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            string filename;
            cout << "Enter filename: ";
            cin >> filename;

            Graph* g = ParseAdjacencyMatrix(filename);
            if (g != nullptr)
            {
                if (graph != nullptr) delete graph;
                graph = g;
            }
            break;
        }

        case 2:
        {
            if (!graph)
            {
                cout << "Graph not loaded\n";
                break;
            }

            cout << "1) DFS\n2) BFS\nEnter choice: ";
            int t;
            cin >> t;

            if (t == 1)
            {
                cout << "DFS: ";
                graph->DFS();
            }
            else if (t == 2)
            {
                string start = "A";
                cout << "BFS from \"" << start << "\": ";
                graph->BFS(start);
            }
            break;
        }

        case 3:
        {
            if (!graph)
            {
                cout << "Graph not loaded\n";
                break;
            }
            graph->FindMinSpanningTree();
            break;
        }

        case 4:
        {
            if (!graph)
            {
                cout << "Graph not loaded\n";
                break;
            }
            cout << "Graph:\n";
            graph->Print();
            break;
        }

        case 0:
        {
            if (graph) delete graph;
            return;
        }

        default:
            cout << "Unknown choice, try again\n";
        }
    }
}
