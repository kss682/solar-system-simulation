#include <iostream>
#include<cmath>
#include<fstream>
#include<stdlib.h>
#include<string>
#include<vector>

#include "tree-elements/body.h"
#include "barnes_hut.hpp"

using namespace std;

string FILENAME;
vector<Body> BODIES;

void read_csv(string filename) {
    string line;
    fstream myfile;

    myfile.open(filename, fstream::in);
    if (myfile.is_open()) {
        getline(myfile, line);
        while (getline(myfile, line)) {
            size_t pos = 0;
            vector<string> values;
            while ((pos = line.find(',')) != string::npos) {
                values.push_back(line.substr(0, pos));
                line.erase(0, pos + 1);
            }
            values.push_back(line);
            Body body = Body(values[1], values[2], stod(values[3]),
                             PositionVector(stod(values[4]), stod(values[5]), stod(values[6])),
                             PositionVector(stod(values[7]), stod(values[8]), stod(values[9])), PositionVector());
            BODIES.push_back(body);
        }
        myfile.close();
    } else cout << "Unable to open file";
}

int main(int argc, char *argv[]) {
    FILENAME = "/home/srinidhi/MyWork/SolarSystemStimulation/data/planets.csv";

    read_csv(FILENAME);

    BarnesHut barnes_hut = BarnesHut(BODIES);
    barnes_hut.ComputeBoundingBox();
    barnes_hut.ConstructOctTree();
    barnes_hut.DisplayTree();
    barnes_hut.ComputeMotion();
    barnes_hut.DisplayTree();

    return 0;
}