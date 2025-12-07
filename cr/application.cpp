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


void application() {
    Graph* graph = nullptr;
    int choice = 0;

    string filename = "graph.txt";


    Graph* g = ParseAdjacencyMatrix(filename);
    if (g != nullptr)
    {
        if (graph != nullptr) delete graph;
        graph = g;
    }
    if (!graph)
    {
        cout << "Graph not loaded\n";
    }

    cout << "Graph:\n";
    graph->Print(); cout << endl;

    cout << "1) DFS: ";
    graph->DFS(); cout << endl;

    cout << "2) BFS: ";
    string start = "A";
    cout << "BFS from \"" << start << "\": ";
    graph->BFS(start); cout << endl;

    cout << "Find Min Spanning Tree\n";
    graph->FindMinSpanningTree(); cout << endl;
}


