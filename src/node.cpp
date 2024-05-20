#include "node.hpp"
// UGLY CODE BELOW

Node::Node(double width, double height, double breadth, double nc_x, double nc_y, double nc_z){
    this->body = nullptr;

    this->cen_of_bb.push_back(nc_x);
    this->cen_of_bb.push_back(nc_y);
    this->cen_of_bb.push_back(nc_z);

    this->dim_of_bb.push_back(width);
    this->dim_of_bb.push_back(height);
    this->dim_of_bb.push_back(breadth);   
    this->node_type = NODE_TYPE::LEAF;

    this->total_mass = 0;
    this->center_of_mass.push_back(0);
    this->center_of_mass.push_back(0);
    this->center_of_mass.push_back(0);
}

bool Node::check_bb(double width, double height, double breadth){
    if((abs(width - this->cen_of_bb[0]) <= this->dim_of_bb[0]) 
        && (abs(this->cen_of_bb[1] - height) <= this->dim_of_bb[1]) && abs(this->cen_of_bb[2] - breadth) <= this->dim_of_bb[2]) return true;
    return false;
}

void Node::add_body(Body &body){
    if(this->body == nullptr && (this->node_type == NODE_TYPE::LEAF || this->node_type == NODE_TYPE::ROOT)){
        cout<<"Assigning bodies: "<<body.name<<endl;
        this->body = &body;

        this->total_mass = this->body->mass;
        this->center_of_mass[0] = this->body->pos[0];
        this->center_of_mass[1] = this->body->pos[1];
        this->center_of_mass[2] = this->body->pos[2];
        return;
    }

    if(this->children.size() == 0) this->generate_children();
 
    if(this->body != nullptr){
        if(this->children[0].check_bb(this->body->pos[0], this->body->pos[1], this->body->pos[2])) this->children[0].add_body(*(this->body));
        else if(this->children[1].check_bb(this->body->pos[0], this->body->pos[1], this->body->pos[2])) this->children[1].add_body(*(this->body)); 
        else if(this->children[2].check_bb(this->body->pos[0], this->body->pos[1], this->body->pos[2])) this->children[2].add_body(*(this->body));
        else if(this->children[3].check_bb(this->body->pos[0], this->body->pos[1], this->body->pos[2])) this->children[3].add_body(*(this->body));
        else if(this->children[4].check_bb(this->body->pos[0], this->body->pos[1], this->body->pos[2])) this->children[4].add_body(*(this->body));
        else if(this->children[5].check_bb(this->body->pos[0], this->body->pos[1], this->body->pos[2])) this->children[5].add_body(*(this->body));
        else if(this->children[6].check_bb(this->body->pos[0], this->body->pos[1], this->body->pos[2])) this->children[6].add_body(*(this->body));
        else if(this->children[7].check_bb(this->body->pos[0], this->body->pos[1], this->body->pos[2])) this->children[7].add_body(*(this->body));
        this->body = nullptr;
        this->node_type = NODE_TYPE::INTERNAL;
    }

    if(this->children[0].check_bb(body.pos[0], body.pos[1], body.pos[2])) this->children[0].add_body(body);
    else if(this->children[1].check_bb(body.pos[0], body.pos[1], body.pos[2])) this->children[1].add_body(body); 
    else if(this->children[2].check_bb(body.pos[0], body.pos[1], body.pos[2])) this->children[2].add_body(body);
    else if(this->children[3].check_bb(body.pos[0], body.pos[1], body.pos[2])) this->children[3].add_body(body);
    else if(this->children[4].check_bb(body.pos[0], body.pos[1], body.pos[2])) this->children[4].add_body(body);
    else if(this->children[5].check_bb(body.pos[0], body.pos[1], body.pos[2])) this->children[5].add_body(body);
    else if(this->children[6].check_bb(body.pos[0], body.pos[1], body.pos[2])) this->children[6].add_body(body);
    else if(this->children[7].check_bb(body.pos[0], body.pos[1], body.pos[2])) this->children[7].add_body(body);

    this->update_center_of_mass();
}

void Node::display_node(){
    if(this->body == nullptr) return;
    cout<<"Body name: "<<this->body->name<<endl;
    cout<<"Body pos: "<<this->body->pos[0]<<" "<<this->body->pos[1]<<""<<this->body->pos[2]<<endl;
    cout<<"Bounding box: "<<this->cen_of_bb[0]<<" "<<this->cen_of_bb[1]<<" "<<this->cen_of_bb[2]<<endl;
    cout<<"Total Mass: "<<this->total_mass<<endl;
    cout<<"Center of Mass: "<<this->center_of_mass[0]<<" "<<this->center_of_mass[1]<<" "<<this->center_of_mass[2]<<endl;
}

double Node::get_total_mass(){
    return this->total_mass;
}

Body* Node::get_body(){
    return this->body;
}

vector<double> Node::get_center_of_mass(){
    return this->center_of_mass;
}

vector<Node> Node::get_children(){
    return this->children;
}

void Node::generate_children(){
    this->children.push_back(Node(this->dim_of_bb[0]/2, this->dim_of_bb[1]/2, this->dim_of_bb[2]/2, this->cen_of_bb[0] + this->dim_of_bb[0]/2, this->cen_of_bb[1] + this->dim_of_bb[1]/2, this->cen_of_bb[2] + this->dim_of_bb[2]/2));  
    this->children.push_back(Node(this->dim_of_bb[0]/2, this->dim_of_bb[1]/2, this->dim_of_bb[2]/2, this->cen_of_bb[0] - this->dim_of_bb[0]/2, this->cen_of_bb[1] + this->dim_of_bb[1]/2, this->cen_of_bb[2] + this->dim_of_bb[2]/2));
    this->children.push_back(Node(this->dim_of_bb[0]/2, this->dim_of_bb[1]/2, this->dim_of_bb[2]/2, this->cen_of_bb[0] - this->dim_of_bb[0]/2, this->cen_of_bb[1] - this->dim_of_bb[1]/2, this->cen_of_bb[2] + this->dim_of_bb[2]/2));
    this->children.push_back(Node(this->dim_of_bb[0]/2, this->dim_of_bb[1]/2, this->dim_of_bb[2]/2, this->cen_of_bb[0] + this->dim_of_bb[0]/2, this->cen_of_bb[1] - this->dim_of_bb[1]/2, this->cen_of_bb[2] + this->dim_of_bb[2]/2));      
    this->children.push_back(Node(this->dim_of_bb[0]/2, this->dim_of_bb[1]/2, this->dim_of_bb[2]/2, this->cen_of_bb[0] + this->dim_of_bb[0]/2, this->cen_of_bb[1] + this->dim_of_bb[1]/2, this->cen_of_bb[2] - this->dim_of_bb[2]/2));  
    this->children.push_back(Node(this->dim_of_bb[0]/2, this->dim_of_bb[1]/2, this->dim_of_bb[2]/2, this->cen_of_bb[0] - this->dim_of_bb[0]/2, this->cen_of_bb[1] + this->dim_of_bb[1]/2, this->cen_of_bb[2] - this->dim_of_bb[2]/2));  
    this->children.push_back(Node(this->dim_of_bb[0]/2, this->dim_of_bb[1]/2, this->dim_of_bb[2]/2, this->cen_of_bb[0] - this->dim_of_bb[0]/2, this->cen_of_bb[1] - this->dim_of_bb[1]/2, this->cen_of_bb[2] - this->dim_of_bb[2]/2));  
    this->children.push_back(Node(this->dim_of_bb[0]/2, this->dim_of_bb[1]/2, this->dim_of_bb[2]/2, this->cen_of_bb[0] + this->dim_of_bb[0]/2, this->cen_of_bb[1] - this->dim_of_bb[1]/2, this->cen_of_bb[2] - this->dim_of_bb[2]/2));    
}

void Node::reset_cm(){
    this->total_mass = 0;
    this->center_of_mass.clear();
    this->center_of_mass.push_back(0);
    this->center_of_mass.push_back(0);
    this->center_of_mass.push_back(0);
}

void Node::update_center_of_mass(){
    this->reset_cm();

    for(Node child: this->get_children()){
        this->total_mass += child.get_total_mass();

        this->center_of_mass[0] += child.get_center_of_mass()[0]*child.get_total_mass();
        this->center_of_mass[1] += child.get_center_of_mass()[1]*child.get_total_mass();
        this->center_of_mass[2] += child.get_center_of_mass()[2]*child.get_total_mass();
    }

    this->center_of_mass[0] /= this->total_mass;
    this->center_of_mass[1] /= this->total_mass;
    this->center_of_mass[2] /= this->total_mass;
}