#include <vector>
#include <unordered_map>

using namespace std;

class EmergencyResponseGraph {
    private:
        unordered_map<int, vector<pair<int, float>>> adjList;
        unordered_map<int, pair<float, float>> coordinates;

    public:
        EmergencyResponseGraph() {};
        void insertEdge(int source, int dest, float dist);
        void insertCoordinates(int vertex, float lat, float lon);
        vector<int> getAdjacent(int vertex);
        float getDistance(int source, int dest);
        vector<int> getVertices() const;
        vector<tuple<int, int, float>> getEdges() const;
};

