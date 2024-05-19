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
    
    for(int i = 0; i < this->bodies.size(); i++){
        cout<<"Adding "<<this->bodies[i].name<<" to oct tree"<<endl;
        if(this->root==nullptr){
            cout<<"Creating the first node"<<endl;
            this->root = new Node(this->bodies[i], this->bb_width, this->bb_height, this->bb_breadth, 0, 0, 0);
        }else{
            this->root->add_body(this->bodies[i]);
            cout<<this->bodies[i].name<<endl;
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
    for(int i = 0; i < node.get_children().size(); i++){
        this->display_node(node.get_children()[i]);
    }
}


