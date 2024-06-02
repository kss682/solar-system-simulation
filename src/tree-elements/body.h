//
// Created by C G Giridhar on 20/05/24.
//
#include <string>
#include <spdlog/spdlog.h>

#include "../units/position_vector.h"

using namespace std;

#ifndef SOLAR_SYS_SIM_BODY_H
#define SOLAR_SYS_SIM_BODY_H

class Body {
private:
    string name;
    string type;
    double mass;
    PositionVector position;
    PositionVector velocity;
    PositionVector acceleration;

public:
    Body(string name, string type, double mass, PositionVector position, PositionVector velocity,
         PositionVector acceleration);

    string get_name();

    string get_type();

    double get_mass();

    PositionVector get_position();

    PositionVector get_velocity();

    PositionVector get_accerleration();

    void set_velocity(PositionVector velocity);

    void update_position(PositionVector position);
    void update_velocity(PositionVector velocity);
    void update_acceleration(PositionVector acceleration);
};


#endif //SOLAR_SYS_SIM_BODY_H
