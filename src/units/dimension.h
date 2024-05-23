//
// Created by C G Giridhar on 20/05/24.
//

#ifndef SOLAR_SYS_SIM_DIMENSION_H
#define SOLAR_SYS_SIM_DIMENSION_H

#include <cmath>
using namespace std;

class Dimension {
private:
    double length;
    double height;
    double depth;
public:
    Dimension();

    Dimension(double length, double height, double depth);

    // Dimension(Dimension &d);

    double get_length();

    double get_depth();

    double get_height();

    double GetMaxValue();
};


#endif //SOLAR_SYS_SIM_DIMENSION_H
