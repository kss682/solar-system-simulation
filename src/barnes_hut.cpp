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

void BarnesHut::ComputeMotion(){
    for(int i = 0; i < this->bodies.size(); i++){
        cout<<"Computing forces for: "<<bodies[i].get_name()<<endl;
        Traverse(bodies[i], *(this->root));
        UpdateVelocity(bodies[i]);
        UpdatePosition(bodies[i]);
    }
}

void BarnesHut::Traverse(Body &body, Box &box){
    if(body.get_name().compare("Sun") == 0) return;

    if(box.get_box_type() == BOX_TYPE::INTERNAL && Threshold(body, box.get_center_of_mass(), box.get_dimensions())) {
        ComputeAcceleration(body, box.get_total_mass(), box.get_center_of_mass());
        return;   
    }
   
   
    if((box.get_box_type() == BOX_TYPE::LEAF 
        && box.get_body() != nullptr) && (box.get_body()->get_name().compare(body.get_name()) != 0)) {
        ComputeAcceleration(body, box.get_total_mass(), box.get_center_of_mass());
        return;       
    }
    


    for(int i = 0; i < box.get_sub_boxes().size(); i++){
        Traverse(body, box.get_sub_boxes()[i]);
    }
}

bool BarnesHut::Threshold(Body body, PositionVector center_of_mass, Dimension dim){
    PositionVector temp = body.get_position() - center_of_mass;
    double th = sqrt(pow(temp.get_x(), 2) + pow(temp.get_y(), 2) + pow(temp.get_z(), 2))/(2*dim.get_length());
    
    if(th <= this->threshold) true;
    return false;
}

void BarnesHut::ComputeAcceleration(Body &body1, double mass, PositionVector r2){
    double scalar = (this->G*mass);
    PositionVector relat_dist = r2 - body1.get_position();

    scalar /= pow((pow(relat_dist.get_x(), 2) + pow(relat_dist.get_y(), 2) + pow(relat_dist.get_z(), 2) + pow(this->epsilon, 2)), 1.5);

    body1.set_acceleration(relat_dist*scalar);
}

void BarnesHut::UpdateVelocity(Body &body){
    body.set_velocity(body.get_accerleration()*this->delta/2);
}

void BarnesHut::UpdatePosition(Body &body){
    body.set_position(body.get_velocity()*this->delta/2);
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
