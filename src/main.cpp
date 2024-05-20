#include <iostream>
#include<cmath>
#include<fstream>
#include<stdlib.h>
#include<string>
#include<vector>

#include "barnes_hut.hpp"
#include "node.hpp"

using namespace std;

string FILENAME;
vector<Body> BODIES;

void read_csv(string filename){
    string line;
    fstream myfile;

    myfile.open(filename, fstream::in);
    if (myfile.is_open())
    {
        getline(myfile, line);
        while ( getline (myfile,line) )
        {
            size_t pos = 0;
            vector<string> values;
            while((pos = line.find(',')) != string::npos){
                values.push_back(line.substr(0, pos));
                line.erase(0, pos+1);
            } 
            values.push_back(line);

            Body *body = new Body{
                name: values[1],
                typ: values[2],
                mass: stod(values[3]),
            };
            body->pos.push_back(stod(values[4]));
            body->pos.push_back(stod(values[5]));
            body->pos.push_back(stod(values[6]));
            body->vel.push_back(stod(values[7]));
            body->vel.push_back(stod(values[8]));
            body->vel.push_back(stod(values[9]));
            BODIES.push_back(*body);
        }
        myfile.close();
    }
    else cout << "Unable to open file"; 
}

int main(int argc, char *argv[]){
    FILENAME = "/home/srinidhi/MyWork/SolarSystemStimulation/data/planets_and_moons_state_vectors.csv";

    read_csv(FILENAME);

    BarnesHut barnes_hut = BarnesHut(BODIES);

    // barnes_hut.clear_oct_tree();
    barnes_hut.compute_bounding_box();
    barnes_hut.construct_oct_tree();
    // barnes_hut.compute_forces();
    barnes_hut.display_tree();
    

    return 0;
}