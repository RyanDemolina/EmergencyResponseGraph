#include "src/EmergencyResponseGraph.h"


void EmergencyResponseGraph::insertEdge(int source, int dest, float dist) {
    adjList[source].push_back(make_pair(dest, dist));
    adjList[dest].push_back(make_pair(source, dist));
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


