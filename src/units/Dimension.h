//
// Created by C G Giridhar on 20/05/24.
//

#ifndef SOLAR_SYS_SIM_DIMENSION_H
#define SOLAR_SYS_SIM_DIMENSION_H

#include <cmath>

class Dimension {
private:
    double length;
    double width;
    double height;
public:
    Dimension();

    Dimension(double length, double width, double height);

    Dimension(double unit);

    Dimension(Dimension const &d);

    double getLength() const;

    double getWidth() const;

    double getHeight() const;

    double getMaxValue() const;
};


#endif //SOLAR_SYS_SIM_DIMENSION_H
