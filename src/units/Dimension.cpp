//
// Created by C G Giridhar on 20/05/24.
//

#include "Dimension.h"

using namespace std;

Dimension::Dimension(double length, double width, double height) : length(length), width(width), height(height) {}

Dimension::Dimension() {
    length = 0;
    width = 0;
    height = 0;
}

Dimension::Dimension(double unit) {

}

Dimension::Dimension(const Dimension &d) {
    length = d.length;
    width = d.width;
    height = d.height;
}

double Dimension::getLength() const {
    return length;
}

double Dimension::getWidth() const {
    return width;
}

double Dimension::getHeight() const {
    return height;
}

double Dimension::getMaxValue() const {
    return std::fmax(height, fmax(length, width));
}
