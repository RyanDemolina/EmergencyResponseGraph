#include "EmergencyResponseGraph.h"
#include <vector>
#include <algorithm>
#include <limits>
#include <stdexcept>
#include <queue>
using namespace std;


vector<int> shortestBellmanFordPath(
    const EmergencyResponseGraph& graph,
    int source,
    int target
);
