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

// Writes the coordinates of the path to a specified csv file
void write_path_to_csv(EmergencyResponseGraph &graph, vector<int> path, string filename) {
   string file_path = "../" + filename;
   ofstream outputFile(file_path, ios::out);
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

    // Iterate through each row of the csv file
    string line, word;
    while (getline(fin, line)) {
        vector<string> row;

        stringstream s(line);

        // Reads each column from the current row
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

        // Insert the edge into the graph along with coordinates of each vertex
        graph.insertEdge(stoi(source), stoi(destination), stof(distance));
        graph.insertCoordinates(stoi(source), stof(source_lat), stof(source_long));
        graph.insertCoordinates(stoi(destination), stof(dest_lat), stof(dest_long));
    }

    // Creates dummy vertices that are not connected to any other vertices
    for (int i = 0; i < 148619; i++) {
        if (graph.getCoordinates(i).first == 0) {
            graph.insertVertex(i);
        }
    }
    fin.close();
    
    int source = graph.getHospitalVertex();
    int dest = -1;
    cout << "An Emergency Has Appeared!!!" << endl;
    cout << endl;

    // Loops through the user menu until a valid option os selected
    while (dest == -1) {
        int select;
        cout << "Please Select An Option:" << endl;
        cout << "1. Select Target Destination" << endl;
        cout << "2. Generate Random Destination" << endl;
        cout << "Choice:";
        cin >> select;

        // Allows the user to choose a destination vertex
        if (select == 1) {
            cout << "Choose a Number Between 0 and " << (graph.getVertices().size() - 1) << endl;
            cout << "Your Desired Destination: ";
            cin >> dest;
        }

        // Chooses a random vertex from the graph as the destination
        else if (select == 2) {
            dest = rand() % (graph.getVertices().size() - 1);
        }
        else {
            cout << "Whoops! Not a Valid Option" << endl;
            continue;
        }
    }

    cout << endl;

    // Runs and times Dijkstra's Algorithm
    Djikstras d;
    auto start = high_resolution_clock::now();
    vector<int> Dijkstra = d.shortestPath(graph, source, dest);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Time Taken For Dijkstra's Algorithm: " << duration.count() << " milliseconds" << endl;

    // Runs and times Bellman-Ford Algorithm
    start = high_resolution_clock::now();
    vector<int> Bellman_Ford = shortestBellmanFordPath(graph, source, dest);
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start);
    cout << "Time Taken For Bellman-Ford Algorithm: " << duration.count() << " milliseconds" << endl;

    cout << endl;

    // If a path exists, it is written to a csv file
    if (Dijkstra.empty()) {
        cout << "Sorry! No Path Was Found" << endl;
    }
    else {
        write_path_to_csv(graph, Dijkstra, "Dijkstra.csv");
        cout << "Path Written To Dijkstra.csv" << endl;

        write_path_to_csv(graph, Dijkstra, "BellmanFord.csv");
        cout << "Path Written To BellmanFord.csv" << endl;
    }
    return 0;
}