#include "EmergencyResponseGraph.h"
#include <vector>
#include <algorithm>
#include <limits>
#include <stdexcept>
using namespace std;


vector<int> shortestBellmanFordPath(
    const EmergencyResponseGraph& graph,
    int source,
    int target
);