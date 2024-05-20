#include<iostream>
#include<vector>
#include "node.hpp"
using namespace std;

#ifndef BARNES_HPP
#define BARNES_HPP

class BarnesHut{
    public:
    BarnesHut(vector<Body> bodies);
    void clear_oct_tree();
    void compute_bounding_box();
    void construct_oct_tree();
    void compute_forces();
    void display_tree();
    void display_node(Node node);

    private: 
    double theta;
    double delta;
    double bb_width, bb_height, bb_breadth;
    
    Node *root;
    vector<Body> bodies;
};

#endif