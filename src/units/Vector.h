//
// Created by C G Giridhar on 20/05/24.
//

#ifndef SOLAR_SYS_SIM_VECTOR_H
#define SOLAR_SYS_SIM_VECTOR_H

class Vector {
private:
    double x;
    double y;
    double z;
public:
    Vector();

    Vector(double x, double y, double z);

    Vector(Vector const &v);

    double getX() const;

    double getY() const;

    double getZ() const;

    Vector operator+(const Vector &rhs) const;

    Vector operator/(double unit) const;
};


#endif //SOLAR_SYS_SIM_VECTOR_H
