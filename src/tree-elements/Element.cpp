//
// Created by C G Giridhar on 20/05/24.
//

#include "Element.h"


Element::Element(Body body, const BoundingBox &boundingBox) : body(&body), boundingBox(boundingBox) {
    totalMass += body.getMass();
}

Element::Element(const BoundingBox &boundingBox) : boundingBox(boundingBox) {
    body = nullptr;
}

void Element::addBody(Body &body) {
    if (this->body == nullptr && (this->nodeType == NODE_TYPE::LEAF || this->nodeType == NODE_TYPE::ROOT)) {
        cout << "Assigning bodies: " << body.getName() << endl;
        this->body = &body;
        this->totalMass += this->body->getMass();
        this->centerOfMass = Vector(body.getPosition());
        return;
    }

    if (this->children.size() == 0) this->generateChildren();

    if (this->body != nullptr) {
        if (boundingBox.has(this->children[0].body->getPosition()))
            this->children[0].addBody(*(this->body));
        else if (boundingBox.has(this->children[1].body->getPosition()))
            this->children[1].addBody(*(this->body));
        else if (boundingBox.has(this->children[2].body->getPosition()))
            this->children[2].addBody(*(this->body));
        else if (boundingBox.has(this->children[3].body->getPosition()))
            this->children[3].addBody(*(this->body));
        else if (boundingBox.has(this->children[4].body->getPosition()))
            this->children[4].addBody(*(this->body));
        else if (boundingBox.has(this->children[5].body->getPosition()))
            this->children[5].addBody(*(this->body));
        else if (boundingBox.has(this->children[6].body->getPosition()))
            this->children[6].addBody(*(this->body));
        else if (boundingBox.has(this->children[7].body->getPosition()))
            this->children[7].addBody(*(this->body));
        this->body = nullptr;
        this->nodeType = NODE_TYPE::INTERNAL;
    }

    if (boundingBox.has(this->children[0].body->getPosition()))
        this->children[0].addBody(body);
    else if (boundingBox.has(this->children[1].body->getPosition()))
        this->children[1].addBody(body);
    else if (boundingBox.has(this->children[2].body->getPosition()))
        this->children[2].addBody(body);
    else if (boundingBox.has(this->children[3].body->getPosition()))
        this->children[3].addBody(body);
    else if (boundingBox.has(this->children[4].body->getPosition()))
        this->children[4].addBody(body);
    else if (boundingBox.has(this->children[5].body->getPosition()))
        this->children[5].addBody(body);
    else if (boundingBox.has(this->children[6].body->getPosition()))
        this->children[6].addBody(body);
    else if (boundingBox.has(this->children[7].body->getPosition()))
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
    this->children.push_back(
            Element(BoundingBox(Vector(boundingBox.getCenter().getX() + boundingBox.getDimensions().getLength() / 2,
                                       boundingBox.getCenter().getY() + boundingBox.getDimensions().getWidth() / 2,
                                       boundingBox.getCenter().getZ() + boundingBox.getDimensions().getHeight() / 2),
                                Dimension(this->boundingBox.getDimensions().getLength() / 2,
                                          this->boundingBox.getDimensions().getWidth() / 2,
                                          boundingBox.getDimensions().getHeight() / 2))));

    this->children.push_back(
            Element(BoundingBox(Vector(boundingBox.getCenter().getX() - boundingBox.getDimensions().getLength() / 2,
                                       boundingBox.getCenter().getY() + boundingBox.getDimensions().getWidth() / 2,
                                       boundingBox.getCenter().getZ() + boundingBox.getDimensions().getHeight() / 2),
                                Dimension(this->boundingBox.getDimensions().getLength() / 2,
                                          this->boundingBox.getDimensions().getWidth() / 2,
                                          boundingBox.getDimensions().getHeight() / 2))));

    this->children.push_back(
            Element(BoundingBox(Vector(boundingBox.getCenter().getX() - boundingBox.getDimensions().getLength() / 2,
                                       boundingBox.getCenter().getY() - boundingBox.getDimensions().getWidth() / 2,
                                       boundingBox.getCenter().getZ() + boundingBox.getDimensions().getHeight() / 2),
                                Dimension(this->boundingBox.getDimensions().getLength() / 2,
                                          this->boundingBox.getDimensions().getWidth() / 2,
                                          boundingBox.getDimensions().getHeight() / 2))));

    this->children.push_back(
            Element(BoundingBox(Vector(boundingBox.getCenter().getX() + boundingBox.getDimensions().getLength() / 2,
                                       boundingBox.getCenter().getY() - boundingBox.getDimensions().getWidth() / 2,
                                       boundingBox.getCenter().getZ() + boundingBox.getDimensions().getHeight() / 2),
                                Dimension(this->boundingBox.getDimensions().getLength() / 2,
                                          this->boundingBox.getDimensions().getWidth() / 2,
                                          boundingBox.getDimensions().getHeight() / 2))));

    this->children.push_back(
            Element(BoundingBox(Vector(boundingBox.getCenter().getX() + boundingBox.getDimensions().getLength() / 2,
                                       boundingBox.getCenter().getY() + boundingBox.getDimensions().getWidth() / 2,
                                       boundingBox.getCenter().getZ() - boundingBox.getDimensions().getHeight() / 2),
                                Dimension(this->boundingBox.getDimensions().getLength() / 2,
                                          this->boundingBox.getDimensions().getWidth() / 2,
                                          boundingBox.getDimensions().getHeight() / 2))));

    this->children.push_back(
            Element(BoundingBox(Vector(boundingBox.getCenter().getX() - boundingBox.getDimensions().getLength() / 2,
                                       boundingBox.getCenter().getY() + boundingBox.getDimensions().getWidth() / 2,
                                       boundingBox.getCenter().getZ() - boundingBox.getDimensions().getHeight() / 2),
                                Dimension(this->boundingBox.getDimensions().getLength() / 2,
                                          this->boundingBox.getDimensions().getWidth() / 2,
                                          boundingBox.getDimensions().getHeight() / 2))));

    this->children.push_back(
            Element(BoundingBox(Vector(boundingBox.getCenter().getX() - boundingBox.getDimensions().getLength() / 2,
                                       boundingBox.getCenter().getY() - boundingBox.getDimensions().getWidth() / 2,
                                       boundingBox.getCenter().getZ() - boundingBox.getDimensions().getHeight() / 2),
                                Dimension(this->boundingBox.getDimensions().getLength() / 2,
                                          this->boundingBox.getDimensions().getWidth() / 2,
                                          boundingBox.getDimensions().getHeight() / 2))));


    this->children.push_back(
            Element(BoundingBox(Vector(boundingBox.getCenter().getX() + boundingBox.getDimensions().getLength() / 2,
                                       boundingBox.getCenter().getY() - boundingBox.getDimensions().getWidth() / 2,
                                       boundingBox.getCenter().getZ() - boundingBox.getDimensions().getHeight() / 2),
                                Dimension(this->boundingBox.getDimensions().getLength() / 2,
                                          this->boundingBox.getDimensions().getWidth() / 2,
                                          boundingBox.getDimensions().getHeight() / 2))));
}

void Element::displayElement() {
    if (this->body == nullptr) return;
    cout << "Body name: " << this->body->getName() << endl;
    cout << "Body pos: " << this->body->getPosition().getX() << " " << this->body->getPosition().getY() << ""
         << this->body->getPosition().getZ() << endl;
//    cout<<"Bounding box: "<<boundingBox.get<<" "<<this->cen_of_bb[1]<<" "<<this->cen_of_bb[2]<<endl;
//    cout<<"Total Mass: "<<this->total_mass<<endl;
//    cout<<"Center of Mass: "<<this->center_of_mass[0]<<" "<<this->center_of_mass[1]<<" "<<this->center_of_mass[2]<<endl;
}

vector<Element> Element::getChildren() {
    return this->children;
}
