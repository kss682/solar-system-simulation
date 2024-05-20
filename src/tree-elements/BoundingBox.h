//
// Created by C G Giridhar on 20/05/24.
//


#ifndef SOLAR_SYS_SIM_BOUNDINGBOX_H
#define SOLAR_SYS_SIM_BOUNDINGBOX_H

#include "../units/Vector.h"
#include "../units/Dimension.h"

#include<iostream>
#include<algorithm>

class BoundingBox {
private:
    Vector center;
    Dimension dimensions;
public:
    BoundingBox(const Vector &center, const Dimension &dimensions);

    BoundingBox();

    const Vector &getCenter() const;

    const Dimension &getDimensions() const;

    void setCenter(const Vector &center);

    void setDimensions(const Dimension &dimensions);

    bool has(Vector point);

    double getInitialBoundingDimension(Vector position);
};


#endif //SOLAR_SYS_SIM_BOUNDINGBOX_H
