#include "Graph.h"
#include <iostream>

Graph::Graph(int v)
{
    V = v;
    for (int i = 0; i < MAX_VERTICES; ++i)
    {
        names[i][0] = '\0';
        adjCount[i] = 0;
        for (int j = 0; j < MAX_EDGES_PER_VERTEX; ++j)
        {
            adj[i][j].src = adj[i][j].dest = -1;
            adj[i][j].weight = 0;
        }
    }
}

void Graph::SetVertexName(int idx, const char* name)
{
    if (idx < 0 || idx >= MAX_VERTICES) return;
    std::strncpy(names[idx], name, NAME_LEN - 1);
    names[idx][NAME_LEN - 1] = '\0';
}

int Graph::FindVertexIndex(const char* name) const {
    for (int i = 0; i < V; ++i) {
        if (std::strcmp(names[i], name) == 0) return i;
    }
    return -1;
}

void Graph::AddEdgeByIndex(int vi, int vj, int weight) {
    if (vi < 0 || vi >= V || vj < 0 || vj >= V) return;
    // avoid duplicate identical edge in same adjacency list
    for (int k = 0; k < adjCount[vi]; ++k) {
        if (adj[vi][k].dest == vj && adj[vi][k].weight == weight) return;
    }
    if (adjCount[vi] < MAX_EDGES_PER_VERTEX) {
        adj[vi][adjCount[vi]].src = vi;
        adj[vi][adjCount[vi]].dest = vj;
        adj[vi][adjCount[vi]].weight = weight;
        adjCount[vi]++;
    }
    // add reverse (undirected)
    for (int k = 0; k < adjCount[vj]; ++k) {
        if (adj[vj][k].dest == vi && adj[vj][k].weight == weight) return;
    }
    if (adjCount[vj] < MAX_EDGES_PER_VERTEX) {
        adj[vj][adjCount[vj]].src = vj;
        adj[vj][adjCount[vj]].dest = vi;
        adj[vj][adjCount[vj]].weight = weight;
        adjCount[vj]++;
    }
}

void Graph::DFS() {
    bool visited[MAX_VERTICES];
    for (int i = 0; i < V; ++i) visited[i] = false;
    for (int i = 0; i < V; ++i) {
        if (!visited[i]) {
            DFSFun(i, visited);
        }
    }
    std::cout << std::endl;
}

void Graph::DFSFun(int v, bool visited[]) {
    visited[v] = true;
    std::cout << names[v] << " ";
    for (int k = 0; k < adjCount[v]; ++k) {
        int to = adj[v][k].dest;
        if (!visited[to]) DFSFun(to, visited);
    }
}

void Graph::BFS(const char* startName) {
    int start = FindVertexIndex(startName);
    if (start == -1) {
        std::cout << "Start vertex not found\n";
        return;
    }
    bool visited[MAX_VERTICES];
    for (int i = 0; i < V; ++i) visited[i] = false;

    // simple circular queue implemented with array
    int q[MAX_VERTICES];
    int front = 0, back = 0;
    auto qpush = [&](int x) { q[back++] = x; };
    auto qpop = [&]() { return q[front++]; };
    auto qempty = [&]() { return front == back; };

    visited[start] = true;
    qpush(start);

    while (!qempty()) {
        int u = qpop();
        std::cout << names[u] << " ";
        for (int k = 0; k < adjCount[u]; ++k) {
            int to = adj[u][k].dest;
            if (!visited[to]) {
                visited[to] = true;
                qpush(to);
            }
        }
    }
    std::cout << std::endl;
}

void Graph::Print() {
    for (int i = 0; i < V; ++i) {
        std::cout << names[i] << " -> ";
        if (adjCount[i] == 0) {
            std::cout << "(no edges)";
        } else {
            for (int k = 0; k < adjCount[i]; ++k) {
                int d = adj[i][k].dest;
                int w = adj[i][k].weight;
                std::cout << "(" << names[d] << ", " << w << ") ";
            }
        }
        std::cout << std::endl;
    }
}

// collect unique edges (only src < dest) into outEdges, return count
int Graph::CollectEdges(Edge outEdges[], int maxEdges) {
    int count = 0;
    for (int i = 0; i < V; ++i) {
        for (int k = 0; k < adjCount[i]; ++k) {
            int j = adj[i][k].dest;
            int w = adj[i][k].weight;
            if (i < j) { // take only once
                if (count < maxEdges) {
                    outEdges[count].src = i;
                    outEdges[count].dest = j;
                    outEdges[count].weight = w;
                    count++;
                }
            }
        }
    }
    return count;
}

void Graph::InsertionSortByWeight(Edge arr[], int n) {
    for (int i = 1; i < n; ++i) {
        Edge key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].weight > key.weight) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int Graph::FindParent(int parent[], int i) {
    while (parent[i] != -1) i = parent[i];
    return i;
}

void Graph::UnionParents(int parent[], int x, int y) {
    parent[y] = x;
}

void Graph::FindMinSpanningTree() {
    Edge edgesList[MAX_EDGES];
    int edgesCount = CollectEdges(edgesList, MAX_EDGES);

    if (edgesCount == 0) {
        std::cout << "No edges in graph\n";
        return;
    }

    // sort by weight ascending
    InsertionSortByWeight(edgesList, edgesCount);

    int parent[MAX_VERTICES];
    for (int i = 0; i < V; ++i) parent[i] = -1;

    Edge mst[MAX_EDGES];
    int mstCount = 0;
    int totalWeight = 0;

    for (int i = 0; i < edgesCount && mstCount < V - 1; ++i) {
        int x = FindParent(parent, edgesList[i].src);
        int y = FindParent(parent, edgesList[i].dest);

        if (x != y) {
            mst[mstCount++] = edgesList[i];
            totalWeight += edgesList[i].weight;
            UnionParents(parent, x, y);
        }
    }

    std::cout << "Edges in MST are:\n";
    // sort mst by src,dest lexicographically by indices' names (simple insertion on small array)
    for (int i = 1; i < mstCount; ++i) {
        Edge key = mst[i];
        int j = i - 1;
        auto compare = [&](const Edge& a, const Edge& b) -> bool {
            int cmpSrc = std::strcmp(names[a.src], names[b.src]);
            if (cmpSrc != 0) return cmpSrc > 0;
            return std::strcmp(names[a.dest], names[b.dest]) > 0;
        };
        while (j >= 0 && compare(mst[j], key)) {
            mst[j + 1] = mst[j];
            j--;
        }
        mst[j + 1] = key;
    }

    for (int i = 0; i < mstCount; ++i) {
        std::cout << names[mst[i].src] << " -- " << names[mst[i].dest] << " (" << mst[i].weight << ")\n";
    }
    std::cout << "Average Weight = " << totalWeight << std::endl;
}
