//
// Created by C G Giridhar on 20/05/24.
//
#include<cmath>

using namespace std;
#ifndef SOLAR_SYS_SIM_PositionVector_H
#define SOLAR_SYS_SIM_PositionVector_H

class PositionVector {
private:
    double x;
    double y;
    double z;
public:
    PositionVector();

    PositionVector(double x, double y, double z);

    // PositionVector(PositionVector &v);

    double get_x();

    double get_y();

    double get_z();

    double GetMaxAbsoluteValue();

    PositionVector operator+(PositionVector rhs);

    PositionVector &operator+=(PositionVector rhs);

    PositionVector operator-(PositionVector rhs);

    PositionVector operator*(double unit);

    PositionVector operator/(double unit);
};


#endif //SOLAR_SYS_SIM_PositionVector_H
