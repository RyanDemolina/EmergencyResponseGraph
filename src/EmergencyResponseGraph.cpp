#include "src/EmergencyResponseGraph.h"
#include <tuple>

// Creates a vertex with no adjacent vertices
void EmergencyResponseGraph::insertVertex(int vertex) {
    adjList[vertex] = {};
}

// Adds the destination vertex and distance to the source vertex's list
// Adds a new vertex to the graph if it does not exist
void EmergencyResponseGraph::insertEdge(int source, int dest, float dist) {
    adjList[source].push_back(make_pair(dest, dist));
    adjList[dest].push_back(make_pair(source, dist));
}

// Stores the coordinates for a given vertex
void EmergencyResponseGraph::insertCoordinates(int vertex, float lat, float lon) {
    if (coordinates.find(vertex) == coordinates.end()) {
        coordinates[vertex] = make_pair(lat, lon);
    }
}

// Returns all vertices adjacent to the given vertex
vector<int> EmergencyResponseGraph::getAdjacent(int vertex) const{
    vector<int> adjacent;
    for (auto& p : adjList.at(vertex)) {
        adjacent.push_back(p.first);
    }
    return adjacent;
}

// Returns the distance between two specified vertices and 0 is no edge exists between them
float EmergencyResponseGraph::getDistance(int source, int dest) const {
    for (auto& adjacent : adjList.at(source)) {
        if (adjacent.first == dest) {
            return adjacent.second;
        }
    }
    return 0;
}

// Returns a vector of all vertices in the graph
vector<int> EmergencyResponseGraph::getVertices() const {
    vector<int> vertices;
    vertices.reserve(adjList.size());
    for (auto& kv : adjList) {
        vertices.push_back(kv.first);
    }
    return vertices;
}

// Returns a vector of all edges in the graph
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

// Returns a pair containing the coordinates of a given vertex
pair<float, float> EmergencyResponseGraph::getCoordinates(int vertex) {
    if (coordinates.find(vertex) == coordinates.end()) {
        return make_pair(0, 0);
    }
    return coordinates[vertex];
}

// Returns the ID of the vertex that the "Hospital" is located at
// This is used as the source vertex for all paths found
int EmergencyResponseGraph::getHospitalVertex() {
    return hospital_vertex;
}

