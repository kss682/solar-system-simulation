#include "box.h"

Box::Box(PositionVector center, Dimension dimension){
    this->center = center;
    this->center_of_mass = PositionVector();
    this->dimension = dimension;
    this->body = nullptr;
    this->box_type = BOX_TYPE::LEAF;
    this->total_mass = 0;
}

Box::Box() {
    this->center = PositionVector();
    this->dimension = Dimension();
}

double Box::get_total_mass(){
    return this->total_mass;
}

Body* Box::get_body(){
    return this->body;
}

PositionVector Box::get_center(){
    return this->center;
}

PositionVector Box::get_center_of_mass(){
    return this->center_of_mass;
}

Dimension Box::get_dimensions(){
    return this->dimension;
}

BOX_TYPE Box::get_box_type(){
    return this->box_type;
}

vector<Box> Box::get_sub_boxes(){
    return this->sub_boxes;
}

void Box::set_center(PositionVector center) {
    this->center = center;
}

void Box::set_center_of_mass(PositionVector center_of_mass){
    this->center_of_mass = center_of_mass;
}
void Box::set_dimensions(Dimension dimension) {
    this->dimension = dimension;
}

void Box::set_box_type(BOX_TYPE box_type){
    this->box_type = box_type;
}

bool Box::Has(PositionVector point) {
    return ((abs(point.get_x() - this->get_center().get_x()) <= this->get_dimensions().get_length())
            && (abs(point.get_y() - this->get_center().get_y()) <= this->get_dimensions().get_height())
            && abs(point.get_z() - this->get_center().get_z()) <= this->get_dimensions().get_depth());
}

void Box::AddBody(Body &body){
    if(this->body == nullptr && (this->box_type == BOX_TYPE::LEAF || this->box_type == BOX_TYPE::ROOT)){
        this->body = &body;
        this->total_mass = body.get_mass();
        this->center_of_mass = body.get_position();
        return;
    }

    if(this->sub_boxes.size() == 0) this->GenerateChildren();
    
    if(this->body != nullptr){
        if(this->sub_boxes[0].Has(this->body->get_position())) this->sub_boxes[0].AddBody(*(this->body));
        else if(this->sub_boxes[1].Has(this->body->get_position())) this->sub_boxes[1].AddBody(*(this->body));
        else if(this->sub_boxes[2].Has(this->body->get_position())) this->sub_boxes[2].AddBody(*(this->body));
        else if(this->sub_boxes[3].Has(this->body->get_position())) this->sub_boxes[3].AddBody(*(this->body));
        else if(this->sub_boxes[4].Has(this->body->get_position())) this->sub_boxes[4].AddBody(*(this->body));
        else if(this->sub_boxes[5].Has(this->body->get_position())) this->sub_boxes[5].AddBody(*(this->body));
        else if(this->sub_boxes[6].Has(this->body->get_position())) this->sub_boxes[6].AddBody(*(this->body));
        else if(this->sub_boxes[7].Has(this->body->get_position())) this->sub_boxes[7].AddBody(*(this->body));
        this->body = nullptr;
        this->box_type = BOX_TYPE::INTERNAL;
    }

    if(this->sub_boxes[0].Has(body.get_position())) this->sub_boxes[0].AddBody(body);
    else if(this->sub_boxes[1].Has(body.get_position())) this->sub_boxes[1].AddBody(body);
    else if(this->sub_boxes[2].Has(body.get_position())) this->sub_boxes[2].AddBody(body);
    else if(this->sub_boxes[3].Has(body.get_position())) this->sub_boxes[3].AddBody(body);
    else if(this->sub_boxes[4].Has(body.get_position())) this->sub_boxes[4].AddBody(body);
    else if(this->sub_boxes[5].Has(body.get_position())) this->sub_boxes[5].AddBody(body);
    else if(this->sub_boxes[6].Has(body.get_position())) this->sub_boxes[6].AddBody(body);
    else if(this->sub_boxes[7].Has(body.get_position())) this->sub_boxes[7].AddBody(body);

    this->UpdateCenterOfMass();
    return;
}

void Box::DisplayBox(){
    cout<<"Bounding box: "<<this->get_dimensions().get_length()<<" "<<this->get_dimensions().get_height()<<" "<<this->get_dimensions().get_depth()<<endl;
    cout<<"Box Mass: "<<this->get_total_mass()<<endl;
    cout<<"Center of Mass: "<<this->get_center_of_mass().get_x()<<" "<<this->get_center_of_mass().get_y()<<" "<<this->get_center_of_mass().get_z()<<endl;
    
    if(this->get_body() != nullptr) {
        cout<<"Body name: "<<this->get_body()->get_name()<<endl;
        cout<<"Body pos: "<<this->get_body()->get_position().get_x()<<" "<<this->get_body()->get_position().get_y()<<" "<<this->get_body()->get_position().get_z()<<endl;
        cout<<"Total Mass: "<<this->get_body()->get_mass()<<endl;
    }
}

void Box::GenerateChildren(){
    this->sub_boxes.push_back(
        Box(
            PositionVector(
                this->center.get_x()/2 + this->dimension.get_length()/2, 
                this->center.get_y()/2 + this->dimension.get_height()/2, 
                this->center.get_z()/2 + this->dimension.get_depth()/2
            ), 
            Dimension(
                this->dimension.get_length()/2, 
                this->dimension.get_height()/2, 
                this->dimension.get_depth()/2
            )
        )
    );
    this->sub_boxes.push_back(
        Box(
            PositionVector(
                this->center.get_x()/2 - this->dimension.get_length()/2, 
                this->center.get_y()/2 + this->dimension.get_height()/2, 
                this->center.get_z()/2 + this->dimension.get_depth()/2
            ), 
            Dimension(
                this->dimension.get_length()/2, 
                this->dimension.get_height()/2, 
                this->dimension.get_depth()/2
            )
        )
    );
    this->sub_boxes.push_back(
        Box(
            PositionVector(
                this->center.get_x()/2 - this->dimension.get_length()/2, 
                this->center.get_y()/2 - this->dimension.get_height()/2, 
                this->center.get_z()/2 + this->dimension.get_depth()/2
            ), 
            Dimension(
                this->dimension.get_length()/2, 
                this->dimension.get_height()/2, 
                this->dimension.get_depth()/2
            )
        )
    );
    this->sub_boxes.push_back(
        Box(
            PositionVector(
                this->center.get_x()/2 + this->dimension.get_length()/2, 
                this->center.get_y()/2 - this->dimension.get_height()/2, 
                this->center.get_z()/2 + this->dimension.get_depth()/2
            ), 
            Dimension(
                this->dimension.get_length()/2, 
                this->dimension.get_height()/2, 
                this->dimension.get_depth()/2
            )
        )
    );
    this->sub_boxes.push_back(
        Box(
            PositionVector(
                this->center.get_x()/2 + this->dimension.get_length()/2, 
                this->center.get_y()/2 + this->dimension.get_height()/2, 
                this->center.get_z()/2 - this->dimension.get_depth()/2
            ), 
            Dimension(
                this->dimension.get_length()/2,
                 this->dimension.get_height()/2, 
                 this->dimension.get_depth()/2
                )
        )
    );
    this->sub_boxes.push_back(
        Box(
            PositionVector(
                this->center.get_x()/2 - this->dimension.get_length()/2, 
                this->center.get_y()/2 + this->dimension.get_height()/2, 
                this->center.get_z()/2 - this->dimension.get_depth()/2
            ), 
            Dimension(this->dimension.get_length()/2, this->dimension.get_height()/2, this->dimension.get_depth()/2)
        )
    );
    this->sub_boxes.push_back(
        Box(
            PositionVector(this->center.get_x()/2 - this->dimension.get_length()/2, this->center.get_y()/2 - this->dimension.get_height()/2, this->center.get_z()/2 - this->dimension.get_depth()/2), 
            Dimension(this->dimension.get_length()/2, this->dimension.get_height()/2, this->dimension.get_depth()/2)
        )
    );
    this->sub_boxes.push_back(
        Box(
            PositionVector(this->center.get_x()/2 + this->dimension.get_length()/2, this->center.get_y()/2 - this->dimension.get_height()/2, this->center.get_z()/2 - this->dimension.get_depth()/2), 
            Dimension(this->dimension.get_length()/2, this->dimension.get_height()/2, this->dimension.get_depth()/2)
        )
    );
}


void Box::UpdateCenterOfMass(){
    this->total_mass = 0;
    this->center_of_mass = PositionVector();

    for(auto box: this->sub_boxes){
        if(box.get_body() == nullptr) continue;
        this->total_mass += box.get_body()->get_mass();
        this->center_of_mass += (box.get_body()->get_position()*box.get_body()->get_mass());
    }
    this->center_of_mass = this->center_of_mass / this->total_mass;
}