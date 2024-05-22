//
// Created by C G Giridhar on 20/05/24.
//

#include "Element.h"


Element::Element(const BoundingBox &boundingBox) : boundingBox(boundingBox) {
    body = nullptr;
    nodeType = NODE_TYPE::LEAF;
    totalMass = 0;
}

Element::Element(const BoundingBox &boundingBox, NODE_TYPE nodeType) :
        boundingBox(boundingBox),
        nodeType(nodeType) {
    body = nullptr;
    totalMass = 0;
}

void Element::addBody(Body &body) {
    if (this->body == nullptr && (this->nodeType == NODE_TYPE::LEAF || this->nodeType == NODE_TYPE::ROOT)) {
        cout << "Assigning bodies: " << body.getName() << endl;
        this->body = &body;
        this->totalMass += this->body->getMass();
        this->centerOfMass = Vector(body.getPosition());
        return;
    }

    if (this->children.empty()) this->generateChildren();

    if (this->body != nullptr) {
        if (children[0].boundingBox.has(this->body->getPosition()))
            this->children[0].addBody(*(this->body));
        else if (children[1].boundingBox.has(this->body->getPosition()))
            this->children[1].addBody(*(this->body));
        else if (children[2].boundingBox.has(this->body->getPosition()))
            this->children[2].addBody(*(this->body));
        else if (children[3].boundingBox.has(this->body->getPosition()))
            this->children[3].addBody(*(this->body));
        else if (children[4].boundingBox.has(this->body->getPosition()))
            this->children[4].addBody(*(this->body));
        else if (children[5].boundingBox.has(this->body->getPosition()))
            this->children[5].addBody(*(this->body));
        else if (children[6].boundingBox.has(this->body->getPosition()))
            this->children[6].addBody(*(this->body));
        else if (children[7].boundingBox.has(this->body->getPosition()))
            this->children[7].addBody(*(this->body));
        this->body = nullptr;
        this->nodeType = NODE_TYPE::INTERNAL;
    }

    if (children[0].boundingBox.has(body.getPosition()))
        this->children[0].addBody(body);
    else if (children[1].boundingBox.has(body.getPosition()))
        this->children[1].addBody(body);
    else if (children[2].boundingBox.has(body.getPosition()))
        this->children[2].addBody(body);
    else if (children[3].boundingBox.has(body.getPosition()))
        this->children[3].addBody(body);
    else if (children[4].boundingBox.has(body.getPosition()))
        this->children[4].addBody(body);
    else if (children[5].boundingBox.has(body.getPosition()))
        this->children[5].addBody(body);
    else if (children[6].boundingBox.has(body.getPosition()))
        this->children[6].addBody(body);
    else if (children[7].boundingBox.has(body.getPosition()))
        this->children[7].addBody(body);
    this->updateCenterOfMass();

}

void Element::resetCm() {
    this->totalMass = 0;
    this->centerOfMass = Vector();
}

void Element::updateCenterOfMass() {
    resetCm();
    for (const Element &child: this->children) {
        this->totalMass += child.totalMass;
        this->centerOfMass = centerOfMass + Vector(child.centerOfMass.getX() * child.totalMass,
                                                   child.centerOfMass.getY() * child.totalMass,
                                                   child.centerOfMass.getZ() * child.totalMass);
    }
    centerOfMass = centerOfMass / totalMass;
}

void Element::generateChildren() {
    this->children.emplace_back(
            BoundingBox(Vector(boundingBox.getCenter().getX() + boundingBox.getDimensions().getLength() / 2,
                               boundingBox.getCenter().getY() + boundingBox.getDimensions().getWidth() / 2,
                               boundingBox.getCenter().getZ() + boundingBox.getDimensions().getHeight() / 2),
                        Dimension(this->boundingBox.getDimensions().getLength() / 2,
                                  this->boundingBox.getDimensions().getWidth() / 2,
                                  boundingBox.getDimensions().getHeight() / 2)));

    this->children.emplace_back(
            BoundingBox(Vector(boundingBox.getCenter().getX() - boundingBox.getDimensions().getLength() / 2,
                               boundingBox.getCenter().getY() + boundingBox.getDimensions().getWidth() / 2,
                               boundingBox.getCenter().getZ() + boundingBox.getDimensions().getHeight() / 2),
                        Dimension(this->boundingBox.getDimensions().getLength() / 2,
                                  this->boundingBox.getDimensions().getWidth() / 2,
                                  boundingBox.getDimensions().getHeight() / 2)));

    this->children.emplace_back(
            BoundingBox(Vector(boundingBox.getCenter().getX() - boundingBox.getDimensions().getLength() / 2,
                               boundingBox.getCenter().getY() - boundingBox.getDimensions().getWidth() / 2,
                               boundingBox.getCenter().getZ() + boundingBox.getDimensions().getHeight() / 2),
                        Dimension(this->boundingBox.getDimensions().getLength() / 2,
                                  this->boundingBox.getDimensions().getWidth() / 2,
                                  boundingBox.getDimensions().getHeight() / 2)));

    this->children.emplace_back(
            BoundingBox(Vector(boundingBox.getCenter().getX() + boundingBox.getDimensions().getLength() / 2,
                               boundingBox.getCenter().getY() - boundingBox.getDimensions().getWidth() / 2,
                               boundingBox.getCenter().getZ() + boundingBox.getDimensions().getHeight() / 2),
                        Dimension(this->boundingBox.getDimensions().getLength() / 2,
                                  this->boundingBox.getDimensions().getWidth() / 2,
                                  boundingBox.getDimensions().getHeight() / 2)));

    this->children.emplace_back(
            BoundingBox(Vector(boundingBox.getCenter().getX() + boundingBox.getDimensions().getLength() / 2,
                               boundingBox.getCenter().getY() + boundingBox.getDimensions().getWidth() / 2,
                               boundingBox.getCenter().getZ() - boundingBox.getDimensions().getHeight() / 2),
                        Dimension(this->boundingBox.getDimensions().getLength() / 2,
                                  this->boundingBox.getDimensions().getWidth() / 2,
                                  boundingBox.getDimensions().getHeight() / 2)));

    this->children.emplace_back(
            BoundingBox(Vector(boundingBox.getCenter().getX() - boundingBox.getDimensions().getLength() / 2,
                               boundingBox.getCenter().getY() + boundingBox.getDimensions().getWidth() / 2,
                               boundingBox.getCenter().getZ() - boundingBox.getDimensions().getHeight() / 2),
                        Dimension(this->boundingBox.getDimensions().getLength() / 2,
                                  this->boundingBox.getDimensions().getWidth() / 2,
                                  boundingBox.getDimensions().getHeight() / 2)));

    this->children.emplace_back(
            BoundingBox(Vector(boundingBox.getCenter().getX() - boundingBox.getDimensions().getLength() / 2,
                               boundingBox.getCenter().getY() - boundingBox.getDimensions().getWidth() / 2,
                               boundingBox.getCenter().getZ() - boundingBox.getDimensions().getHeight() / 2),
                        Dimension(this->boundingBox.getDimensions().getLength() / 2,
                                  this->boundingBox.getDimensions().getWidth() / 2,
                                  boundingBox.getDimensions().getHeight() / 2)));


    this->children.emplace_back(
            BoundingBox(Vector(boundingBox.getCenter().getX() + boundingBox.getDimensions().getLength() / 2,
                               boundingBox.getCenter().getY() - boundingBox.getDimensions().getWidth() / 2,
                               boundingBox.getCenter().getZ() - boundingBox.getDimensions().getHeight() / 2),
                        Dimension(this->boundingBox.getDimensions().getLength() / 2,
                                  this->boundingBox.getDimensions().getWidth() / 2,
                                  boundingBox.getDimensions().getHeight() / 2)));
}

void Element::displayElement() {
    if (this->body == nullptr) return;
    cout << endl << this->body->getName() << endl << "===============================" << endl;
    cout << "Body pos: [" << this->body->getPosition().getX() << ", " << this->body->getPosition().getY() << ", "
         << this->body->getPosition().getZ() << " ]" << endl;
    cout << "Bounding Box \n Dimensions : [l = " << boundingBox.getDimensions().getLength() << ", w = "
         << boundingBox.getDimensions().getWidth() << ", h = " << boundingBox.getDimensions().getHeight() << " ]"
         << "\n Center : [ " << boundingBox.getCenter().getX() << ", " << boundingBox.getCenter().getY() << ", "
         << boundingBox.getCenter().getZ() << " ]" << endl;
    cout << "Total Mass: " << this->totalMass << endl;
}

vector<Element> Element::getChildren() {
    return this->children;
}
