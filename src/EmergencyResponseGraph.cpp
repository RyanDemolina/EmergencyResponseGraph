#include "src/EmergencyResponseGraph.h"


void EmergencyResponseGraph::insertEdge(int source, int dest, float dist) {
    adjList[source].push_back(make_pair(dest, dist));
    if (adjList.find(dest) == adjList.end()) {
        adjList[dest] = {};
    }
}

void EmergencyResponseGraph::insertCoordinates(int vertex, float lat, float lon) {
    if (coordinates.find(vertex) == coordinates.end()) {
        coordinates[vertex] = make_pair(lat, lon);
    }
}

vector<int> EmergencyResponseGraph::getAdjacent(int vertex) {
    vector<int> adjacent;
    for (pair<int, float> adj: adjList[vertex]) {
        adjacent.push_back(adj.first);
    }
    return adjacent;
}

float EmergencyResponseGraph::getDistance(int source, int dest) {
    for (pair<int, float> adj: adjList[source]) {
        if (adj.first == dest) {
            return adj.second;
        }
    }
    return 0;
}

vector<int> EmergencyResponseGraph::getVertices() const {
    vector<int> vertices;
    vertices.reserve(adjList.size());
    for (auto& kv : adjList) {
        vertices.push_back(kv.first);
    }
    return vertices;
}


vector<tuple<int, int, float>> EmergencyResponseGraph::getEdges() const {
    vector<tuple< int, int, float>> edges;
    for (auto& kv : adjList) {
        int u = kv.first;
        for (auto& p : kv.second) {
            int v = p.first;
            int w = p.second;
            edges.emplace_back(u, v, w);
        }
    }
    return edges;
}


