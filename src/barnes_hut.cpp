#include "barnes_hut.hpp"

BarnesHut::BarnesHut(vector<Body> bodies){
    this->bodies = bodies;
    this->root = nullptr;
}

void BarnesHut::ClearOctTree(){
    return;
}


void BarnesHut::ComputeBoundingBox(){
    double max_bb = 0;
    for(auto body: this->bodies){
        max_bb = fmax(max_bb, body.get_position().GetMaxAbsoluteValue());
    }

    this->dimension = Dimension(max_bb, max_bb, max_bb);
}

void BarnesHut::ConstructOctTree(){
    for(int i = 0; i < this->bodies.size(); i++){
        cout<<"Adding "<<this->bodies[i].get_name()<<" to oct tree"<<endl;
        if(this->root==nullptr) this->root = new Box(PositionVector(0, 0, 0), this->dimension);
        this->root->AddBody(this->bodies[i]);
    }
}



void BarnesHut::DisplayTree(){
    DisplayBox(*(this->root));
}

void BarnesHut::DisplayBox(Box box){
    box.DisplayBox();
    for(int i = 0; i < box.get_sub_boxes().size(); i++){
        this->DisplayBox(box.get_sub_boxes()[i]);
    }
}
