#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <utility>
#include <limits>
#include <unordered_map>
#include <algorithm>

class Graph {
public:
    int V; // Number of vertices
    std::unordered_map<int, std::list<std::pair<int, int>>> adj; // Adjacency list

    Graph(int V);
    void addEdge(int u, int v, int w);
    void dijkstra(int src, int dest);
};

#endif // GRAPH_H

#include "Graph.h"

Graph::Graph(int V) {
    this->V = V;
}

void Graph::addEdge(int u, int v, int w) {
    adj[u].push_back(std::make_pair(v, w));
    adj[v].push_back(std::make_pair(u, w));
}

void Graph::dijkstra(int src, int dest) {
    std::set<std::pair<int, int>> setds;
    std::vector<int> dist(V, std::numeric_limits<int>::max());
    std::vector<int> parent(V, -1);

    setds.insert(std::make_pair(0, src));
    dist[src] = 0;

    while (!setds.empty()) {
        std::pair<int, int> tmp = *(setds.begin());
        setds.erase(setds.begin());
        int u = tmp.second;

        for (auto i = adj[u].begin(); i != adj[u].end(); ++i) {
            int v = (*i).first;
            int weight = (*i).second;

            if (dist[v] > dist[u] + weight) {
                if (dist[v] != std::numeric_limits<int>::max()) {
                    setds.erase(setds.find(std::make_pair(dist[v], v)));
                }

                dist[v] = dist[u] + weight;
                parent[v] = u;
                setds.insert(std::make_pair(dist[v], v));
            }
        }
    }

    std::cout << "Shortest distance from " << src << " to " << dest << " is " << dist[dest] << std::endl;

    // Print the path
    std::vector<int> path;
    for (int v = dest; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    std::reverse(path.begin(), path.end());

    std::cout << "Path: ";
    for (size_t i = 0; i < path.size(); i++) {
        std::cout << path[i];
        if (i < path.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
}


#include <iostream>
#include "Graph.h"

int main() {
    int V = 9;
    Graph g(V);

    // Add edges to the graph
    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);

    int src, dest;
    std::cout << "Enter source node: ";
    std::cin >> src;
    std::cout << "Enter destination node: ";
    std::cin >> dest;

    g.dijkstra(src, dest);

    return 0;
}
