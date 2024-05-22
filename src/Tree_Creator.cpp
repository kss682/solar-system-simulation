//
// Created by C G Giridhar on 20/05/24.
//

#include "Tree_Creator.h"
#include "tree-elements/Element.h"

#include <iostream>

Tree_Creator::Tree_Creator(const vector<Body> &bodies) {
    root = nullptr;
    this->bodies = bodies;
}

void Tree_Creator::clearOctTree() {
    return;
}

void Tree_Creator::computeBoundingBox() {
    double maxDimension = 0;
    for (const Body &body: this->bodies) {
        maxDimension = boundingBox.getInitialBoundingDimension(body.getPosition());
    }
    boundingBox.setDimensions(Dimension(maxDimension));
}

void Tree_Creator::constructOctTree() {
    for (int i = 0; i < this->bodies.size(); i++) {
        cout << "Adding " << this->bodies[i].getName() << " to oct tree" << endl;
        if (this->root == nullptr)
            this->root = new Element(boundingBox, NODE_TYPE::ROOT);
        this->root->addBody(this->bodies[i]);
    }
    cout << "Tree Constructed" << endl;
}

void Tree_Creator::computeForces() {
    return;
}

void Tree_Creator::displayTree() {
    displayElement(*(this->root));
}

void Tree_Creator::displayElement(Element element) {
    element.displayElement();
    for (int i = 0; i < element.getChildren().size(); i++) {
        this->displayElement(element.getChildren()[i]);
    }
}


