//
// Created by C G Giridhar on 20/05/24.
//

#include "position_vector.h"

PositionVector::PositionVector(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

PositionVector::PositionVector() {
    x = 0;
    y = 0;
    z = 0;
}

// PositionVector::PositionVector(PositionVector &v) {
//     x = v.x;
//     y = v.y;
//     z = v.z;
// }

double PositionVector::get_x() {
    return x;
}

double PositionVector::get_y() {
    return y;
}

double PositionVector::get_z() {
    return z;
}

double PositionVector::GetMaxAbsoluteValue() {
    return fmax(this->x, fmax(this->y, this->z));
}

PositionVector PositionVector::operator+(PositionVector rhs) {
    return {x + rhs.x, y + rhs.y, z + rhs.z};
}

PositionVector &PositionVector::operator+=(PositionVector rhs) {
    this->x += rhs.get_x();
    this->y += rhs.get_y();
    this->z += rhs.get_z();

    return *this;
}

PositionVector PositionVector::operator-(PositionVector rhs) {
    return {x - rhs.x, y - rhs.y, z - rhs.z};
}

PositionVector PositionVector::operator*(double unit) {
    return {this->x * unit, this->y * unit, this->z * unit};
}

PositionVector PositionVector::operator/(double unit) {
    return {this->x / unit, this->y / unit, this->z / unit};
}


