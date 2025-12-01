#include "Graph.h"
#include <iostream>

Graph::Graph(int v)
{
    V = v;

    for (int i = 0; i < MAX_VERTICES; ++i)
    {
        names[i] = "";
        adjCount[i] = 0;

        for (int j = 0; j < MAX_EDGES_PER_VERTEX; ++j)
        {
            adj[i][j].src = -1;
            adj[i][j].dest = -1;
            adj[i][j].weight = 0;
        }
    }
}

void Graph::SetVertexName(int idx, const string& name)
{
    if (idx < 0 || idx >= MAX_VERTICES) return;
    names[idx] = name;
}

int Graph::FindVertexIndex(const string& name) const
{
    for (int i = 0; i < V; ++i)
    {
        if (names[i] == name)
            return i;
    }
    return -1;
}

void Graph::AddEdgeByIndex(int vi, int vj, int weight)
{
    if (vi < 0 || vi >= V || vj < 0 || vj >= V) return;

    for (int k = 0; k < adjCount[vi]; ++k)
    {
        if (adj[vi][k].dest == vj && adj[vi][k].weight == weight)
            return;
    }
    if (adjCount[vi] < MAX_EDGES_PER_VERTEX)
    {
        adj[vi][adjCount[vi]] = {vi, vj, weight};
        adjCount[vi]++;
    }
    for (int k = 0; k < adjCount[vj]; ++k)
    {
        if (adj[vj][k].dest == vi && adj[vj][k].weight == weight)
            return;
    }
    if (adjCount[vj] < MAX_EDGES_PER_VERTEX)
    {
        adj[vj][adjCount[vj]] = {vj, vi, weight};
        adjCount[vj]++;
    }
}

void Graph::DFS()
{
    bool visited[MAX_VERTICES];

    for (int i = 0; i < V; ++i) visited[i] = false;

    for (int i = 0; i < V; ++i)
    {
        if (!visited[i])
            DFSFun(i, visited);
    }

    cout << endl;
}

void Graph::DFSFun(int v, bool visited[])
{
    visited[v] = true;

    cout << names[v] << " ";

    for (int k = 0; k < adjCount[v]; ++k)
    {
        int to = adj[v][k].dest;
        if (!visited[to])
            DFSFun(to, visited);
    }
}

void Graph::BFS(const string& startName)
{
    int start = FindVertexIndex(startName);
    if (start == -1)
    {
        cout << "Start vertex not found\n";
        return;
    }

    bool visited[MAX_VERTICES];
    for (int i = 0; i < V; i++) visited[i] = false;

    int q[MAX_VERTICES];
    int front = 0, back = 0;

    auto qpush = [&](int x) { q[back++] = x; };
    auto qpop = [&]() { return q[front++]; };
    auto qempty = [&]() { return front == back; };

    visited[start] = true;
    qpush(start);

    while (!qempty())
    {
        int u = qpop();
        cout << names[u] << " ";

        for (int k = 0; k < adjCount[u]; ++k)
        {
            int to = adj[u][k].dest;
            if (!visited[to])
            {
                visited[to] = true;
                qpush(to);
            }
        }
    }
    cout << endl;
}

void Graph::Print()
{
    for (int i = 0; i < V; ++i)
    {
        cout << names[i] << " -> ";

        if (adjCount[i] == 0)
        {
            cout << "(no edges)";
        }
        else
        {
            for (int k = 0; k < adjCount[i]; ++k)
            {
                int d = adj[i][k].dest;
                int w = adj[i][k].weight;
                cout << "(" << names[d] << ", " << w << ") ";
            }
        }

        cout << endl;
    }
}

int Graph::CollectEdges(Edge outEdges[], int maxEdges)
{
    int count = 0;

    for (int i = 0; i < V; ++i)
    {
        for (int k = 0; k < adjCount[i]; ++k)
        {
            int j = adj[i][k].dest;
            int w = adj[i][k].weight;

            if (i < j)
            {
                if (count < maxEdges)
                {
                    outEdges[count++] = {i, j, w};
                }
            }
        }
    }
    return count;
}

void Graph::InsertionSortByWeight(Edge arr[], int n)
{
    for (int i = 1; i < n; ++i)
    {
        Edge key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j].weight > key.weight)
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

int Graph::FindParent(int parent[], int i)
{
    while (parent[i] != -1)
        i = parent[i];
    return i;
}

void Graph::UnionParents(int parent[], int x, int y)
{
    parent[y] = x;
}

void Graph::FindMinSpanningTree()
{
    Edge edgesList[MAX_EDGES];
    int edgesCount = CollectEdges(edgesList, MAX_EDGES);

    if (edgesCount == 0)
    {
        cout << "No edges in graph\n";
        return;
    }

    InsertionSortByWeight(edgesList, edgesCount);

    int parent[MAX_VERTICES];
    for (int i = 0; i < V; i++) parent[i] = -1;

    Edge mst[MAX_EDGES];
    int mstCount = 0;
    int totalWeight = 0;

    for (int i = 0; i < edgesCount && mstCount < V - 1; i++)
    {
        int x = FindParent(parent, edgesList[i].src);
        int y = FindParent(parent, edgesList[i].dest);

        if (x != y) {
            mst[mstCount++] = edgesList[i];
            totalWeight += edgesList[i].weight;
            UnionParents(parent, x, y);
        }
    }

    cout << "Edges in MST are:\n";

    // сортировка по именам вершин
    for (int i = 1; i < mstCount; ++i)
    {
        Edge key = mst[i];
        int j = i - 1;

        auto compare = [&](const Edge& a, const Edge& b)
        {
            if (names[a.src] != names[b.src])
                return names[a.src] > names[b.src];
            return names[a.dest] > names[b.dest];
        };

        while (j >= 0 && compare(mst[j], key))
        {
            mst[j + 1] = mst[j];
            j--;
        }
        mst[j + 1] = key;
    }

    for (int i = 0; i < mstCount; i++)
    {
        cout << names[mst[i].src] << " -- "
                  << names[mst[i].dest] << " ("
                  << mst[i].weight << ")\n";
    }

    cout << "Average Weight = " << totalWeight << endl;
}


