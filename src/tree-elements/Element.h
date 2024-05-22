//
// Created by C G Giridhar on 20/05/24.
//

#ifndef SOLAR_SYS_SIM_ELEMENT_H
#define SOLAR_SYS_SIM_ELEMENT_H

#include<vector>

#include "Body.h"
#include "BoundingBox.h"
#include <iostream>

using namespace std;

enum NODE_TYPE {
    ROOT,
    INTERNAL,
    LEAF
};

class Element {
private:
    Body *body;
    NODE_TYPE nodeType;
    BoundingBox boundingBox;
    double totalMass = 0;
    Vector centerOfMass = Vector();
    vector<Element> children;
public:
    Element(const BoundingBox &boundingBox);
    Element(const BoundingBox &boundingBox, NODE_TYPE nodeType);
    void addBody(Body &body);
    void generateChildren();
    bool checkBoundingBox(Dimension dimension);
    void updateCenterOfMass();
    void resetCm();

    void displayElement();

    vector<Element> getChildren();
};


#endif //SOLAR_SYS_SIM_ELEMENT_H
