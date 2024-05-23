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
    void ComputeMotion();
    void DisplayTree();
    void DisplayBox(Box box);

    private: 
    double G = 6.67430e-11;
    double theta;
    double delta = 25000;
    double threshold = 0.5;
    double epsilon = 1e-11;
    Dimension dimension;
    
    Box *root;
    vector<Body> bodies;

    void Traverse(Body &body, Box &box);
    bool Threshold(Body body, PositionVector center_of_mass, Dimension dim);
    void ComputeAcceleration(Body &body1, double mass, PositionVector r2);
    void UpdateVelocity(Body &body);
    void UpdatePosition(Body &body);
};

#endif