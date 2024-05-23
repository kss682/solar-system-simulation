#include<iostream>
#include<vector>

#include "tree-elements/box.h"
#include "units/dimension.h"
using namespace std;

#ifndef BARNES_HPP
#define BARNES_HPP

class BarnesHut{
    public:
    BarnesHut(vector<Body> bodies);
    void ClearOctTree();
    void ComputeBoundingBox();
    void ConstructOctTree();
    void ComputeForces();
    void DisplayTree();
    void DisplayBox(Box box);

    private: 
    double theta;
    double delta;
    Dimension dimension;
    
    Box *root;
    vector<Body> bodies;
};

#endif