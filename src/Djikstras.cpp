#include "Djikstras.hpp"
typedef Djikstras::DistMap DistMap;
typedef unordered_map<int, int> ParentMap;


struct Node {
    int vertexId;//vertex id
    double dist;//current best known dist
    bool operator>(const Node& right) const { return dist > right.dist;}
    //operator keeps smallest dist on top
};


void Djikstras::runAlgo( EmergencyResponseGraph& graph, int source,
    DistMap& dist, ParentMap& parent) {

    dist[source] = 0.0;//set source dist to 0

    //min heap ordered by smallest dist
    priority_queue<Node, vector<Node>, greater<Node>> prioQ;
    prioQ.push({source, 0.0});

    while (!prioQ.empty()) {
        auto [currentV, currentDist] = prioQ.top();
        prioQ.pop();

        if (currentDist > dist[currentV]) {
            continue;
        }
        for (int neighbor : graph.getAdjacent(currentV)) {

            double pathThruCurrent = dist[currentV] +
                graph.getDistance(currentV, neighbor);

            if (!dist.count(neighbor) or pathThruCurrent < dist[neighbor]) {
                //if we found a shorter path
                dist[neighbor] = pathThruCurrent;
                parent[neighbor] = currentV;
                prioQ.push({neighbor, pathThruCurrent});
            }
        }
    }
}


DistMap Djikstras::shortestDistances(EmergencyResponseGraph& graph, int source) {

    DistMap dist;
    ParentMap temp;

    runAlgo(graph, source, dist, temp);
    return dist;
}

vector<int> Djikstras::shortestPath(EmergencyResponseGraph &graph, int source, int target) {
    DistMap dist;
    ParentMap parent;

    runAlgo(graph, source, dist, parent);

    if (!dist.count(target)) {
        return {};
    }

    vector<int> path;

    for (int itV = target; itV != source; itV = parent[itV]) {
        path.push_back(itV);

    }
    path.push_back(source);
    reverse(path.begin(), path.end());
    return path;
}

