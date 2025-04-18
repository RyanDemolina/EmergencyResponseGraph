#include <iostream>
#include <sstream>
#include <fstream>
#include <src/EmergencyResponseGraph.h>

using namespace std;

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

    
    return 0;
}