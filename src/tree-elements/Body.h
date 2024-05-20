//
// Created by C G Giridhar on 20/05/24.
//
#include <string>

#include "../units/Vector.h"

using namespace std;

#ifndef SOLAR_SYS_SIM_BODY_H
#define SOLAR_SYS_SIM_BODY_H

class Body {
private:
    string name;
    string type;
    double mass;
    Vector position;
    Vector velocity;
    Vector acceleration;

public:
    Body(const string &name, const string &type, double mass, const Vector &position, const Vector &velocity,
         const Vector &acceleration);

    const string &getName() const;

    const string &getType() const;

    double getMass() const;

    const Vector &getPosition() const;

    const Vector &getVelocity() const;

    const Vector &getAcceleration() const;
};


#endif //SOLAR_SYS_SIM_BODY_H
