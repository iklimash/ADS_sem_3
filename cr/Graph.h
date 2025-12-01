#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <cstring>

const int MAX_VERTICES = 50;
const int MAX_EDGES = 50;
const int NAME_LEN = 50;
const int MAX_EDGES_PER_VERTEX = 10; // макс кол-во ребер из одной вершины

struct Edge {
    int src;    // источник
    int dest;   // приемник
    int weight;
};

class Graph {
public:
    int V;

    char names[MAX_VERTICES][NAME_LEN];

    // у каждой вершины есть массив рёбер adj[i]
    // рёбра хранятся в Edge-массивах
    // adjCount[i] — сколько рёбер реально есть
    Edge adj[MAX_VERTICES][MAX_EDGES_PER_VERTEX];
    int adjCount[MAX_VERTICES];

    Graph(int v = 0);

    void SetVertexName(int idx, const char* name);
    int FindVertexIndex(const char* name) const;

    void AddEdgeByIndex(int vi, int vj, int weight);

    void DFS();
    void DFSFun(int v, bool visited[]);
    void BFS(const char* startName);
    void Print();
    // крускал
    void FindMinSpanningTree();

private:

    int CollectEdges(Edge outEdges[], int maxEdges);

    void InsertionSortByWeight(Edge arr[], int n);

    int FindParent(int parent[], int i);
    void UnionParents(int parent[], int x, int y);
};

#endif // GRAPH_H
