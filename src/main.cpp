#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <src/EmergencyResponseGraph.h>
#include <src/Djikstras.hpp>
#include <src/EmergencyResponseBellmanFord.h>

using namespace std;
using namespace std::chrono;

void write_path_to_csv(EmergencyResponseGraph &graph, vector<int> path) {
   ofstream outputFile("path.csv", ios::out);
   for (int v: path) {
       outputFile << graph.getCoordinates(v).first << ", " << graph.getCoordinates(v).second << endl;
   }
   outputFile.close();
}

int main() {

    EmergencyResponseGraph graph;

    fstream fin;
    // Open the file containing graph data
    fin.open("../NewYorkGraphData.csv", ios::in);

    string line, word;
    while (getline(fin, line)) {
        vector<string> row;

        // used for breaking words
        stringstream s(line);

        // read every column data of a row and
        // store it in a string variable, 'word'
        while (getline(s, word, ',')) {
            // add all the column data
            // of a row to a vector
            row.push_back(word);
        }
        string source = row[0];
        string destination = row[1];
        string distance = row[2];
        string source_lat = row[3];
        string source_long = row[4];
        string dest_lat = row[5];
        string dest_long = row[6];

        graph.insertEdge(stoi(source), stoi(destination), stof(distance));
        graph.insertCoordinates(stoi(source), stof(source_lat), stof(source_long));
        graph.insertCoordinates(stoi(destination), stof(dest_lat), stof(dest_long));
    }
    fin.close();

    int source = graph.getHospitalVertex();
    int dest = -1;

    while (dest == -1) {
        int select;
        cout << "Please Select An Option:" << endl;
        cout << "1. Select Target Destination" << endl;
        cout << "2. Generate Random Destination" << endl;
        cout << "Choice:";
        cin >> select;


        if (select == 1) {
            cout << "Choose a Number Between 0 and " << (graph.getVertices().size() - 1) << endl;
            cout << "Your Desired Destination: ";
            cin >> dest;
        } else if (select == 2) {
            dest = rand() % (graph.getVertices().size() - 1);
        } else {
            cout << "Whoops! Not a Valid Option" << endl;
            continue;
        }
    }

    cout << endl;

    Djikstras d;
    auto start = high_resolution_clock::now();
    vector<int> Dijkstra = d.shortestPath(graph, source, dest);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Time Taken For Dijkstra's Algorithm: " << duration.count() << " milliseconds" << endl;

    if (Dijkstra.empty()) {
        cout << "No Path Was Found" << endl;
    }

    start = high_resolution_clock::now();
    vector<int> Bellman_Ford = shortestBellmanFordPath(graph, source, dest);
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start);
    cout << "Time Taken For Bellman-Ford Algorithm: " << duration.count() << " milliseconds" << endl;

    cout << endl;

    write_path_to_csv(graph, Dijkstra);
    cout << "Path Written To path.csv" << endl;
    return 0;
}