//
// Created by C G Giridhar on 20/05/24.
//


#ifndef SOLAR_SYS_SIM_BOUNDINGBOX_H
#define SOLAR_SYS_SIM_BOUNDINGBOX_H

#include <vector>
#include "body.h"
#include "../units/position_vector.h"
#include "../units/dimension.h"

#include<iostream>

using namespace std;

enum BOX_TYPE {
    ROOT,
    INTERNAL,
    LEAF
};


class Box {
private:
    double total_mass;
    Body *body;
    PositionVector center;
    PositionVector center_of_mass;
    Dimension dimension;
    BOX_TYPE box_type;
    vector<Box> sub_boxes;

    void GenerateChildren();

    void UpdateCenterOfMass();

public:
    Box(PositionVector center, Dimension dimension);

    Box();

    ~Box();

    double get_total_mass();

    Body *get_body();

    PositionVector get_center();

    PositionVector get_center_of_mass();

    Dimension get_dimensions();

    BOX_TYPE get_box_type();

    vector<Box> get_sub_boxes();

    void set_total_mass(double total_mass);

    void set_center(PositionVector center);

    void set_center_of_mass(PositionVector center_of_mass);

    void set_dimensions(Dimension dimension);

    void set_box_type(BOX_TYPE box_type);

    bool Has(PositionVector point);

    void AddBody(Body &body);

    void DisplayBox();
};


#endif //SOLAR_SYS_SIM_BOUNDINGBOX_H
