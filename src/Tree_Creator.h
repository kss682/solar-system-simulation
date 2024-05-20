//
// Created by C G Giridhar on 20/05/24.
//

#ifndef SOLAR_SYS_SIM_TREE_CREATOR_H
#define SOLAR_SYS_SIM_TREE_CREATOR_H


#include "units/Dimension.h"
#include "tree-elements/Element.h"

class Tree_Creator {
private:
    double theta;
    double delta;
    BoundingBox boundingBox = BoundingBox();
    Element *root;
    vector<Body> bodies;
public:
    explicit Tree_Creator(const vector<Body> &bodies);
    void clearOctTree();
    void computeBoundingBox();
    void constructOctTree();
    void computeForces();
    void displayTree();
    void displayElement(Element node);
};


#endif //SOLAR_SYS_SIM_TREE_CREATOR_H
