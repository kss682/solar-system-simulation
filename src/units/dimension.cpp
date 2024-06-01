//
// Created by C G Giridhar on 20/05/24.
//

#include "dimension.h"

using namespace std;

Dimension::Dimension(double length, double height, double depth) {
    this->length = length;
    this->height = height;
    this->depth = depth;
}

Dimension::Dimension() {
    this->length = 0;
    this->height = 0;
    this->depth = 0;
}

// Dimension::Dimension(Dimension &d) {
//     this->length = d.length;
//     this->height = d.height;
//     this->depth = d.depth;
// }

double Dimension::get_length() {
    return length;
}

double Dimension::get_depth() {
    return depth;
}

double Dimension::get_height() {
    return height;
}

double Dimension::GetMaxValue() {
    return std::fmax(height, fmax(length, depth));
}
