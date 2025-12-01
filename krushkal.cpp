#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// Structure to represent an edge

struct Edge
{
    int u, v, weight;
};

// Structure for disjoint set
struct DisjointSet
{
    vector<int> parent, rank;

    DisjointSet(int n)
    {
        parent.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void UnionSet(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY)
        {
            if (rank[rootX] < rank[rootY])
            {
                parent[rootX] = rootY;
            }
            else if (rank[rootY] < rank[rootX])
            {
                parent[rootY] = rootX;
            }
            else
            {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};
int main()
{
    int V, E;
    cout << "Enter the number of vertices" << endl;
    cin >> V;
    cout << "Enter the number of edges" << endl;
    cin >> E;

    vector<Edge> edges(E);
    cout << "Enter edges (u v weight)" << endl;
    for (int i = 0; i < E; i++)
    {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    // sort edges by weight
    sort(edges.begin(), edges.end(), [](Edge a, Edge b)
         { return a.weight < b.weight; });

    DisjointSet ds(V);
    vector<Edge> mst;
    int totalweight = 0;

    for (auto &e : edges)
    {
        // Include edge if it doesn't contain any cycle
        if (ds.find(e.u) != ds.find(e.v))
        {
            mst.push_back(e);
            totalweight += e.weight;
            ds.UnionSet(e.u, e.v);
        }
    }

    cout << "MST :" << endl;
    for (auto &e : mst)
    {
        cout << e.u << " -- " << e.v << " | Weight - " << e.weight << endl;
    }

    cout << "Total Weight of MST = " << totalweight << endl;

    return 0;
}