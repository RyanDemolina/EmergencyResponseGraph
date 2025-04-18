#include "EmergencyResponseBellmanFord.h"


vector<int> shortestBellmanFordPath(
    const EmergencyResponseGraph& graph,
    int source,
    int target
) {
    auto vertices = graph.getVertices();
    auto edges = graph.getEdges();

    unordered_map<int, float> dist;
    unordered_map<int, int> pred;

    for (int u : vertices) {
        dist[u] = numeric_limits<float>::infinity();
        pred[u] = -1;
    }
    dist[source] = 0.0f;

    for (size_t i = 1; i < vertices.size(); ++i) {
        for (auto& e : edges) {
            int u, v;
            float w;
            tie(u, v, w) = e;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pred[v] = u;
            }
        }
    }

    for (auto& e : edges) {
        int u, v; 
        float w;
        tie(u, v, w) = e;
        if (dist[u] + w < dist[v]) {
            throw runtime_error("Negative cycle present");
        }
    }

    vector<int> path;
    if (dist[target] == numeric_limits<float>::infinity())
        return path;

    for (int curr = target; curr != -1; curr = pred[curr])
        path.push_back(curr);
    reverse(path.begin(), path.end());
    return path;
}