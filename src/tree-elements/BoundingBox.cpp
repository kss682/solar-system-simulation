//
// Created by C G Giridhar on 20/05/24.
//

#include "BoundingBox.h"

#include<iostream>
#include<algorithm>

BoundingBox::BoundingBox(const Vector &center, const Dimension &dimensions) : center(center), dimensions(dimensions) {}

BoundingBox::BoundingBox() {
    center = Vector();
    dimensions = Dimension();
}

const Vector &BoundingBox::getCenter() const {
    return center;
}

const Dimension &BoundingBox::getDimensions() const {
    return dimensions;
}

void BoundingBox::setCenter(const Vector &center) {
    BoundingBox::center = center;
}

void BoundingBox::setDimensions(const Dimension &dimensions) {
    BoundingBox::dimensions = dimensions;
}

bool BoundingBox::has(Vector point) {
    return ((abs(point.getX() - this->getCenter().getX()) <= this->getDimensions().getLength())
            && (abs(point.getY() - this->getCenter().getY()) <= this->getDimensions().getWidth())
            && abs(point.getZ() - this->getCenter().getZ()) <= this->getDimensions().getHeight());
}

double BoundingBox::getInitialBoundingDimension(Vector position) {
    return fmax(fmax((double) abs(fmax(this->getDimensions().getLength(), abs(position.getX()))) + 1,
                     (double) abs(fmax(this->getDimensions().getWidth(), abs(position.getY()))) + 1),
                (double) abs(fmax(this->getDimensions().getHeight(), abs(position.getZ()))) + 1);
}
