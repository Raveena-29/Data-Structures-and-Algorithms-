#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Structure to represent an edge
struct Edge
{
    int u, v, weight;
};

int main()
{
    int V, E, source;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    vector<Edge> edges(E);

    cout << "Enter edges (u v weight):\n";
    for (int i = 0; i < E; i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;

    cout << "Enter the source vertex: ";
    cin >> source;

    // Distance array
    vector<int> dist(V, INT_MAX);
    dist[source] = 0;

    // Relax edges V-1 times
    for (int i = 1; i <= V - 1; i++)
    {
        for (int j = 0; j < E; j++)
        {
            int u = edges[j].u;
            int v = edges[j].v;
            int wt = edges[j].weight;

            if (dist[u] != INT_MAX && dist[u] + wt < dist[v])
                dist[v] = dist[u] + wt;
        }
    }

    // Check for negative weight cycle
    for (int j = 0; j < E; j++)
    {
        int u = edges[j].u;
        int v = edges[j].v;
        int wt = edges[j].weight;
        if (dist[u] != INT_MAX && dist[u] + wt < dist[v])
        {
            cout << "\nGraph contains a negative weight cycle! Shortest path not possible.\n";
            return 0;
        }
    }

    // Print shortest paths
    cout << "\nShortest distances from source " << source << ":\n";
    for (int i = 0; i < V; i++)
        cout << "To vertex " << i << " = " << dist[i] << endl;

    return 0;
}
