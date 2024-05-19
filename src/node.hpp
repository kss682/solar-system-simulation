#include<iostream>
#include<string>
#include<vector>
// #include "celestial_body.hpp"
using namespace std;


#ifndef NODE_HPP
#define NODE_HPP

enum NODE_TYPE{
    ROOT,
    INTERNAL,
    LEAF 
};

struct Body {
    string name;
    string typ;
    double mass;
    vector<double> pos;
    vector<double> vel;
    vector<double> acc;
};

class Node{
    public:
    Node(Body &body, double width, double height, double breadth, double nc_x, double nc_y, double nc_z);
    Node(double width, double height, double breadth, double nc_x, double nc_y, double nc_z);

    vector<Node> get_children();
    Body* get_body();
    // NODE_TYPE get_nod_type();
    void add_body(Body &body);
    bool check_bb(double width, double height);
    void display_node();

    private:
    // void calc_cm_and_mass();
    // void generate_children();
    // void delete_children();

    // Center of the bounding box
    vector<double> cen_of_bb;
    double total_mass;  
    vector<double> centor_of_mass;
    // Dimensions of the bounding box;
    vector<double> dim_of_bb;
    Body *body;
    NODE_TYPE node_type;
    vector<Node> children;
};

#endif