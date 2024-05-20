#include <iostream>
#include<cmath>
#include<fstream>
#include<stdlib.h>
#include<string>
#include<vector>

#include "tree-elements/Body.h"
#include "tree-elements/Element.h"
#include "Tree_Creator.h"

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
                             Vector(stod(values[4]), stod(values[5]), stod(values[6])),
                             Vector(stod(values[7]), stod(values[8]), stod(values[9])), Vector());
            BODIES.push_back(body);
        }
        myfile.close();
    } else cout << "Unable to open file";
}

int main(int argc, char *argv[]) {
    FILENAME = "/Users/giridhar/Code/Fachpratikum/solar-system-stimulation/data/planets.csv";

    read_csv(FILENAME);

    Tree_Creator barnes_hut = Tree_Creator(BODIES);

    // barnes_hut.clear_oct_tree();
    barnes_hut.computeBoundingBox();
    barnes_hut.constructOctTree();
    // barnes_hut.compute_forces();
    barnes_hut.displayTree();

//    BarnesHut barnes_hut = BarnesHut(BODIES);
//
//    // barnes_hut.clear_oct_tree();
//    barnes_hut.compute_bounding_box();
//    barnes_hut.construct_oct_tree();
//    // barnes_hut.compute_forces();
//    barnes_hut.display_tree();
//    barnes_hut.clear_oct_tree();
//    barnes_hut.display_tree();

    return 0;
}