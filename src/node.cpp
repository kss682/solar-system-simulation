#include "node.hpp"

// This is called when the node is a root
Node::Node(Body &body, double width, double height, double breadth, double nc_x, double nc_y, double nc_z){
    this->body = &body;
    this->cen_of_bb.push_back(nc_x);
    this->cen_of_bb.push_back(nc_y);
    // this->cen_of_bb.push_back(nc_z);

    this->dim_of_bb.push_back(width);
    this->dim_of_bb.push_back(height);
    // this->dim_of_bb.push_back(breadth);
}

Node::Node(double width, double height, double breadth, double nc_x, double nc_y, double nc_z){
    this->body = nullptr;
    this->cen_of_bb.push_back(nc_x);
    this->cen_of_bb.push_back(nc_y);
    // this->cen_of_bb.push_back(nc_z);

    this->dim_of_bb.push_back(width);
    this->dim_of_bb.push_back(height);
    // this->dim_of_bb.push_back(breadth);   
}


void Node::add_body(Body &body){
    if(this->body == nullptr){
        this->body = &body;
        return;
    }

    if(this->children.size() == 0){
        this->children.push_back(
            Node(this->dim_of_bb[0]/2, this->dim_of_bb[1]/2, this->dim_of_bb[2]/2, this->dim_of_bb[0]/2, this->dim_of_bb[1]/2, this->dim_of_bb[2]/2)
        );
        this->children.push_back(
            Node(this->dim_of_bb[0]/2, this->dim_of_bb[1]/2, this->dim_of_bb[2]/2, -1*this->dim_of_bb[0]/2, this->dim_of_bb[1]/2, this->dim_of_bb[2]/2)
        );
        this->children.push_back(
            Node(this->dim_of_bb[0]/2, this->dim_of_bb[1]/2, this->dim_of_bb[2]/2,  this->dim_of_bb[0]/2, -1*this->dim_of_bb[1]/2, this->dim_of_bb[2]/2)
        );
        this->children.push_back(
            Node(this->dim_of_bb[0]/2, this->dim_of_bb[1]/2, this->dim_of_bb[2]/2, -1*this->dim_of_bb[0]/2, -1*this->dim_of_bb[1]/2, this->dim_of_bb[2]/2)
        );
    }

    // First move the existing body in parent node to child, 
    if(this->body != nullptr){
        if(this->children[0].check_bb(this->body->pos[0], this->body->pos[1])) this->children[0].add_body(*(this->body));
        else if(this->children[1].check_bb(this->body->pos[0], this->body->pos[1])) this->children[1].add_body(*(this->body)); 
        else if(this->children[2].check_bb(this->body->pos[0], this->body->pos[1])) this->children[2].add_body(*(this->body));
        else if(this->children[3].check_bb(this->body->pos[0], this->body->pos[1])) this->children[3].add_body(*(this->body));
        this->body = nullptr;
        return;
    }


    if(this->children[0].check_bb(body.pos[0], body.pos[1])) this->children[0].add_body(body);
    else if(this->children[1].check_bb(body.pos[0], body.pos[1])) this->children[1].add_body(body); 
    else if(this->children[2].check_bb(body.pos[0], body.pos[1])) this->children[2].add_body(body);
    else if(this->children[3].check_bb(body.pos[0], body.pos[1])) this->children[3].add_body(body);

}


bool Node::check_bb(double width, double height){
    if((this->cen_of_bb[0] + this->dim_of_bb[0] >= width && this->cen_of_bb[0] - this->dim_of_bb[0] <= width) 
        && (this->cen_of_bb[1] + this->dim_of_bb[1] >= height && this->cen_of_bb[1] - this->dim_of_bb[1] <= height)) return true;
    return false;
}

Body* Node::get_body(){
    return this->body;
}

vector<Node> Node::get_children(){
    return this->children;
}

void Node::display_node(){
    if(this->body == nullptr) return;
    cout<<"Body name: "<<this->body->name<<endl;
    cout<<"Body pos: "<<this->body->pos[0]<<" "<<this->body->pos[1]<<endl;
    cout<<"Bounding box: "<<this->dim_of_bb[0]<<" "<<this->dim_of_bb[1]<<endl;
}