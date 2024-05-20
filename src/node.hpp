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
    Node(double width, double height, double breadth, double nc_x, double nc_y, double nc_z);
    
    bool check_bb(double width, double height, double breadth);
    void add_body(Body &body);
    void display_node();
    double get_total_mass();

    Body* get_body();
    vector<double> get_center_of_mass();
    vector<Node> get_children();
    
    private:
    // void delete_children();
    void generate_children();
    void reset_cm();
    void update_center_of_mass();
    
    double total_mass;

    Body *body;
    NODE_TYPE node_type;
    vector<double> cen_of_bb;
    vector<double> center_of_mass;
    vector<double> dim_of_bb;
    vector<Node> children;
};

#endif