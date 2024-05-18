#include "barnes_hut.hpp"

BarnesHut::BarnesHut(vector<Body> bodies){
    this->bodies = bodies;
    this->bb_breadth = 0;
    this->bb_height = 0;
    this->bb_width = 0;

    this->root = nullptr;
}

void BarnesHut::clear_oct_tree(){
    return;
}

void BarnesHut::compute_bounding_box(){
    for(auto body: this->bodies){
        this->bb_width = (double) abs(max(this->bb_width, abs(body.pos[0]))) + 1;
        this->bb_height = (double) abs(max(this->bb_height, abs(body.pos[1]))) + 1;
        // this->bb_width = max(this->bb_width, abs(body.pos[2]));
    }

    cout<<this->bb_width<<" "<<this->bb_height<<endl;
}

void BarnesHut::construct_oct_tree(){
    
    for(auto body: bodies){
        cout<<"Adding "<<body.name<<" to oct tree"<<endl;
        if(this->root==nullptr){
            cout<<"Creating the first node"<<endl;
            this->root = new Node(body, this->bb_width, this->bb_height, this->bb_breadth, 0, 0, 0);
        }else{
            this->root->add_body(body);
            cout<<body.name<<endl;
        }
    }
}

void BarnesHut::compute_forces(){
    return;
}

void BarnesHut::display_tree(){
    display_node(*(this->root));
}

void BarnesHut::display_node(Node node){
    node.display_node();
}


