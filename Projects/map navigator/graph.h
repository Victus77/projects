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
