#include <iostream>
#include<stdlib.h>
#include<string>
#include<vector>
#include<cmath>
#include<fstream>
#include "node.hpp"
#include "barnes_hut.hpp"
using namespace std;
/*
    Compile all the dependencies to a binary called "stimulate"

    ./stimulate takes the input file, dt - 
*/

vector<Body> bodies;

// Optimize this reading ??
void read_csv(string filename){
    // vector<Body> bodies;

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
            bodies.push_back(*body);
        }
        myfile.close();
    }
    else cout << "Unable to open file"; 


    // return bodies;
}

int main(){
    // Cmd line arguements


    string filename = "/home/srinidhi/MyWork/SolarSystemStimulation/data/planets.csv";
    read_csv(filename);

    BarnesHut barnes_hut = BarnesHut(bodies);

    // barnes_hut.clear_oct_tree();
    barnes_hut.compute_bounding_box();
    barnes_hut.construct_oct_tree();
    // barnes_hut.compute_forces();
    barnes_hut.display_tree();
    

    return 0;
}