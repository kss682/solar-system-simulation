//
// Created by C G Giridhar on 20/05/24.
//

#include "Body.h"

Body::Body(const string &name, const string &type, double mass, const Vector &position, const Vector &velocity,
           const Vector &acceleration) : name(name), type(type), mass(mass), position(position), velocity(velocity),
                                         acceleration(acceleration) {}

const string &Body::getName() const {
    return name;
}

const string &Body::getType() const {
    return type;
}

double Body::getMass() const {
    return mass;
}

const Vector &Body::getPosition() const {
    return position;
}

const Vector &Body::getVelocity() const {
    return velocity;
}

const Vector &Body::getAcceleration() const {
    return acceleration;
}
