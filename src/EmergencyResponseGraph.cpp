#include "src/EmergencyResponseGraph.h"
#include <tuple>


void EmergencyResponseGraph::insertVertex(int vertex) {
    adjList[vertex] = {};
}

void EmergencyResponseGraph::insertEdge(int source, int dest, float dist) {
    adjList[source].push_back(make_pair(dest, dist));
    adjList[dest].push_back(make_pair(source, dist));
}

void EmergencyResponseGraph::insertCoordinates(int vertex, float lat, float lon) {
    if (coordinates.find(vertex) == coordinates.end()) {
        coordinates[vertex] = make_pair(lat, lon);
    }
}

vector<int> EmergencyResponseGraph::getAdjacent(int vertex) const{
    vector<int> adjacent;
    for (auto& p : adjList.at(vertex)) {
        adjacent.push_back(p.first);
    }
    return adjacent;
}

float EmergencyResponseGraph::getDistance(int source, int dest) const {
    for (auto& adjacent : adjList.at(source)) {
        if (adjacent.first == dest) {
            return adjacent.second;
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
            float w = p.second;
            edges.emplace_back(u, v, w);
        }
    }
    return edges;
}

pair<float, float> EmergencyResponseGraph::getCoordinates(int vertex) {
    if (coordinates.find(vertex) == coordinates.end()) {
        return make_pair(0, 0);
    }
    return coordinates[vertex];
}

int EmergencyResponseGraph::getHospitalVertex() {
    return hospital_vertex;
}

