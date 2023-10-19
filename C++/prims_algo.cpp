#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Define a structure to represent a graph edge
struct Edge {
    int destination;
    int weight;
};

// Define a function to find the minimum spanning tree of a graph using Prim's algorithm
vector<vector<Edge>> PrimMST(vector<vector<Edge>>& graph) {
    int V = graph.size(); // Number of vertices

    // Create a min-heap (priority queue) to store edges and their weights
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Initialize a vector to keep track of whether a vertex is included in the MST
    vector<bool> inMST(V, false);

    // Initialize the result MST
    vector<vector<Edge>> MST(V);

    // Start with the first vertex (can start with any vertex)
    int startVertex = 0;
    inMST[startVertex] = true;

    // Add all edges of the start vertex to the priority queue
    for (const Edge& edge : graph[startVertex]) {
        pq.push({edge.weight, edge.destination});
    }

    while (!pq.empty()) {
        int u = pq.top().second; // Get the destination vertex of the edge
        int weight = pq.top().first;
        pq.pop();

        // If including this edge doesn't form a cycle, add it to the MST
        if (!inMST[u]) {
            MST[startVertex].push_back({u, weight});
            MST[u].push_back({startVertex, weight});
            inMST[u] = true;

            // Add all edges of vertex u to the priority queue
            for (const Edge& edge : graph[u]) {
                pq.push({edge.weight, edge.destination});
            }
        }
    }

    return MST;
}

int main() {
    int V = 5; // Number of vertices

    vector<vector<Edge>> graph(V); // Adjacency list representation of the graph

    // Adding edges to the graph
    graph[0].push_back({1, 2});
    graph[0].push_back({3, 6});
    graph[1].push_back({0, 2});
    graph[1].push_back({2, 3});
    graph[1].push_back({3, 8});
    graph[1].push_back({4, 5});
    graph[2].push_back({1, 3});
    graph[2].push_back({4, 7});
    graph[3].push_back({0, 6});
    graph[3].push_back({1, 8});
    graph[3].push_back({4, 9});
    graph[4].push_back({1, 5});
    graph[4].push_back({2, 7});
    graph[4].push_back({3, 9});

    vector<vector<Edge>> MST = PrimMST(graph);

    // Output the Minimum Spanning Tree (MST)
    for (int i = 0; i < V; i++) {
        cout << "Edges connected to vertex " << i << ": ";
        for (const Edge& edge : MST[i]) {
            cout << "(" << edge.destination << ", " << edge.weight << ") ";
        }
        cout << endl;
    }

    return 0;
}
