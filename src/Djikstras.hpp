#pragma once
#include "EmergencyResponseGraph.h"
#include <unordered_map>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;


class Djikstras {
public:
    typedef unordered_map<int, double> DistMap;

    static DistMap shortestDistances(EmergencyResponseGraph& graph, int source);

    static vector<int> shortestPath(EmergencyResponseGraph& graph, int source, int target);


private:
    static void runAlgo(EmergencyResponseGraph& graph, int source,
        DistMap& dist, unordered_map<int, int>& parent);





};