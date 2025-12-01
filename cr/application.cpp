#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Helper to split a line into tokens (space separated)
int SplitTokens(const std::string& line, char tokens[][NAME_LEN], int maxTokens) {
    std::istringstream iss(line);
    std::string t;
    int count = 0;
    while (iss >> t && count < maxTokens) {
        std::strncpy(tokens[count], t.c_str(), NAME_LEN - 1);
        tokens[count][NAME_LEN - 1] = '\0';
        ++count;
    }
    return count;
}

Graph* ParseAdjacencyMatrix(const std::string& filePath) {
    std::ifstream in(filePath.c_str());
    if (!in.is_open()) {
        std::cout << "Error opening file: " << filePath << std::endl;
        return nullptr;
    }

    std::string line;
    if (!std::getline(in, line)) {
        std::cout << "Empty file\n";
        return nullptr;
    }

    char tokens[MAX_VERTICES][NAME_LEN];
    int numVertices = SplitTokens(line, tokens, MAX_VERTICES);
    if (numVertices <= 0) {
        std::cout << "No vertices found\n";
        return nullptr;
    }

    Graph* g = new Graph(numVertices);
    for (int i = 0; i < numVertices; ++i) {
        g->SetVertexName(i, tokens[i]);
    }

    int row = 0;
    while (std::getline(in, line) && row < numVertices) {
        std::istringstream iss(line);
        int weight;
        int col = 0;
        while (iss >> weight && col < numVertices) {
            if (weight > 0 && row <= col) {
                // add each undirected edge only once (row <= col)
                g->AddEdgeByIndex(row, col, weight);
            }
            col++;
        }
        row++;
    }

    in.close();
    return g;
}

void printMenu() {
    std::cout << "Main menu:\n";
    std::cout << "1. Make Graph\n";
    std::cout << "2. Graph traversal\n";
    std::cout << "3. Find Min-Spanning Tree\n";
    std::cout << "4. Print Graph\n";
    std::cout << "5. Exit\n";
}

void application() {
    Graph* graph = nullptr;
    int choice = 0;

    printMenu();
    while (true) {
        std::cout << "Enter your choice: ";
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input\n";
            continue;
        }
        if (choice == 1) {
            std::string filename;
            std::cout << "Enter filename: ";
            std::cin >> filename;
            Graph* g = ParseAdjacencyMatrix(filename);
            if (g != nullptr) {
                if (graph != nullptr) delete graph;
                graph = g;
            }
        } else if (choice == 2) {
            if (graph == nullptr) {
                std::cout << "Graph not loaded\n";
                continue;
            }
            std::cout << "1) DFS\n2) BFS\nEnter choice: ";
            int t;
            std::cin >> t;
            if (t == 1) {
                std::cout << "DFS: ";
                graph->DFS();
            } else if (t == 2) {
                // default start "A" as original
                std::cout << "BFS: ";
                graph->BFS("A");
            }
        } else if (choice == 3) {
            if (graph == nullptr) {
                std::cout << "Graph not loaded\n";
                continue;
            }
            graph->FindMinSpanningTree();
        } else if (choice == 4) {
            if (graph == nullptr) {
                std::cout << "Graph not loaded\n";
                continue;
            }
            std::cout << "Graph:\n";
            graph->Print();
        } else if (choice == 5) {
            if (graph) delete graph;
            return;
        } else {
            std::cout << "Unknown choice\n";
        }
    }
}
