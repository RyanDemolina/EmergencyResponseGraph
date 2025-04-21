#include <vector>
#include <unordered_map>
#pragma once

using namespace std;

class EmergencyResponseGraph {
    private:
        unordered_map<int, vector<pair<int, float>>> adjList;
        unordered_map<int, pair<float, float>> coordinates;
        int hospital_vertex = 1351;

    public:
        EmergencyResponseGraph() {};
        void insertEdge(int source, int dest, float dist);
        void insertCoordinates(int vertex, float lat, float lon);
        vector<int> getAdjacent(int vertex) const;
        float getDistance(int source, int dest) const;
        vector<int> getVertices() const;
        vector<tuple<int, int, float>> getEdges() const;
        pair<float, float> getCoordinates(int vertex);
        int getHospitalVertex();
        void insertVertex(int vertex);
};

