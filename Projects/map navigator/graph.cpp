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
