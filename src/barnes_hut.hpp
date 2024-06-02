#include<iostream>
#include<vector>
#include <spdlog/spdlog.h>

#include "tree-elements/box.h"
#include "units/dimension.h"

#include <vtkSmartPointer.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkNew.h>
#include <vtkSphereSource.h>
#include <vtkGlyph3D.h>
#include <vtkXMLPolyDataWriter.h>


using namespace std;

#ifndef BARNES_HPP
#define BARNES_HPP

class BarnesHut{
    public:
    BarnesHut(vector<Body> bodies);
    void ClearOctTree();
    void ComputeBoundingBox();
    void ConstructOctTree();
    void UpdateInitialVelocity();
    void ComputeMotion();
    void Display();
    void UpdateKE();
    void UpdatePE();
    void CreateVtkFile();

    private:
    double G = 1.48818517e-34;
    double theta;
    double delta = 1;
    double threshold = 1.5;
    double epsilon = 1e-11;
    double KE = 0;
    double PE = 0;
    Dimension dimension;

    Box *root;
    vector<Body> bodies;

    double EuclideanDistance(PositionVector r1, PositionVector r2);
    void ClearBox(Box *box);
    void Traverse(Body &body, Box &box);
    bool Threshold(Body body, PositionVector center_of_mass, Dimension dim);
    void ComputeAcceleration(Body &body1, double mass, PositionVector r2);
    void UpdateVelocity(Body &body);
    void UpdatePosition(Body &body);
};

#endif