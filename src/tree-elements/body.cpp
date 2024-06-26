//
// Created by C G Giridhar on 20/05/24.
//

#include "body.h"

Body::Body(string name, string type, double mass, PositionVector position, PositionVector velocity,
           PositionVector acceleration) {
    spdlog::debug("Initializing Body instance for {}", name);
    this->name = name;
    this->type = type;
    this->mass = mass;
    this->position = position;
    this->velocity = velocity;
    this->acceleration = acceleration;
}

string Body::get_name() {
    return name;
}

string Body::get_type() {
    return type;
}

double Body::get_mass() {
    return mass;
}

PositionVector Body::get_position() {
    return position;
}

PositionVector Body::get_velocity() {
    return velocity;
}

PositionVector Body::get_accerleration() {
    return acceleration;
}

void Body::set_velocity(PositionVector get_velocity){
    this->velocity = velocity;
}

void Body::update_position(PositionVector position) {
    this->position += position;
}

void Body::update_velocity(PositionVector velocity) {
    this->velocity += velocity;
}

void Body::update_acceleration(PositionVector acceleration) {
    this->acceleration += acceleration;
}