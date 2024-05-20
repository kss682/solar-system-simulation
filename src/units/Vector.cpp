//
// Created by C G Giridhar on 20/05/24.
//

#include "Vector.h"

Vector::Vector(double x, double y, double z) : x(x), y(y), z(z) {}

Vector::Vector() {
    x = 0;
    y = 0;
    z = 0;
}


Vector Vector::operator+(const Vector &rhs) const {
    return {x + rhs.x, y + rhs.y, z + rhs.z};
}

Vector::Vector(Vector const &v) {
    x = v.x;
    y = v.y;
    z = v.z;
}

Vector Vector::operator/(double unit) const {
    return {x / unit, y / unit, z / unit};
}

double Vector::getX() const {
    return x;
}

double Vector::getY() const {
    return y;
}

double Vector::getZ() const {
    return z;
}
