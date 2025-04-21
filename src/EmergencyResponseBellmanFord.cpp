#include "EmergencyResponseBellmanFord.h"


// Get sequence of vertices from shortest path
// Using SPFA to make faster 
vector<int> shortestBellmanFordPath(
    const EmergencyResponseGraph& graph,
    int source,
    int target
) {
    // get vertices from graph
    auto vertices = graph.getVertices();

    // initialize distance, predecessor, and maps for SPFA
    unordered_map<int, float> dist;
    unordered_map<int, int> pred;
    unordered_map<int, bool> inQueue;
    unordered_map<int, int> count;

    // set all distances to infinity and predecessors to -1 (none)
    for (int u : vertices) {
        dist[u] = numeric_limits<float>::infinity();
        pred[u] = -1;
        inQueue[u] = false;
        count[u] = 0;
    }
    dist[source] = 0.0f;  // distance to source also 0

    // seed queue
    queue<int> q;
    q.push(source);
    inQueue[source] = true;
    count[source] = 1;

    // SPFA loop
    while (!q.empty()) {
        int u = q.front(); 
        q.pop();
        inQueue[u] = false;
        // relax only the edges out of u
        for (int v : graph.getAdjacent(u)) {
            float w = graph.getDistance(u, v);
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pred[v] = u;
                // enqueue for further relaxation if needed
                if (!inQueue[v]) {
                    q.push(v);
                    inQueue[v] = true;
                    if (++count[v] > (int)vertices.size()) {
                        throw runtime_error("Negative cycle present");
                    }
                }
            }
        }
    }

    // reconstruct path 
    vector<int> path;
    if (dist[target] == numeric_limits<float>::infinity())
        return path;    // if unreachable, return it as empty

    for (int curr = target; curr != -1; curr = pred[curr])
        path.push_back(curr);   // go backwards from target to source 
    reverse(path.begin(), path.end());      // reverse to get in order
    return path;
}
