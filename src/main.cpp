#include <iostream>
#include<cmath>
#include<fstream>
#include<stdlib.h>
#include<string>
#include<vector>
#include <spdlog/spdlog.h>

#include "tree-elements/body.h"
#include "barnes_hut.hpp"

using namespace std;

string FILENAME;
vector<Body> BODIES;

void read_csv(string filename) {
    spdlog::info("Starting to read from CSV");
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
            spdlog::info("Got body : {}", values[1]);
            Body body = Body(values[1], values[2], stod(values[3]),
                             PositionVector(stod(values[4]), stod(values[5]), stod(values[6])),
                             PositionVector(stod(values[7]), stod(values[8]), stod(values[9])), PositionVector());
            BODIES.push_back(body);
        }
        spdlog::info("Successfully read the csv");
        myfile.close();
    } else {
        spdlog::critical("Unable to open the file!");
    }
}

int main(int argc, char *argv[]) {

    spdlog::info("Starting the simulation");

    FILENAME = "/home/srinidhi/MyWork/SolarSystemStimulation/data/planets.csv";;
    spdlog::info("Loading file from : {}", FILENAME);

    read_csv(FILENAME);

    spdlog::info("Initializing Barnes hut simulation");

    BarnesHut barnes_hut = BarnesHut(BODIES);
    barnes_hut.ComputeBoundingBox();
    barnes_hut.ConstructOctTree();
    barnes_hut.DisplayTree();
    barnes_hut.ComputeMotion();
    barnes_hut.DisplayTree();

    return 0;
}