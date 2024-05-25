#include "barnes_hut.hpp"

BarnesHut::BarnesHut(vector<Body> bodies) {
    this->bodies = bodies;
    this->root = nullptr;
}

void BarnesHut::ClearOctTree() {
    return;
}


void BarnesHut::ComputeBoundingBox() {
    spdlog::info("Computing bounding box");
    double max_bb = 0;
    for (auto body: this->bodies) {
        max_bb = fmax(max_bb, body.get_position().GetMaxAbsoluteValue());
    }
    spdlog::info("Max Bounding box found : {}", max_bb);
    this->dimension = Dimension(max_bb, max_bb, max_bb);
}

void BarnesHut::ConstructOctTree() {
    spdlog::info("Constructing Octet tree");
    for (int i = 0; i < this->bodies.size(); i++) {
        spdlog::info("Adding {} to the oct tree", this->bodies[i].get_name());
        if (this->root == nullptr) {
            spdlog::info("Initializing root");
            this->root = new Box(PositionVector(0, 0, 0), this->dimension);
        }
        this->root->AddBody(this->bodies[i]);
    }
}

void BarnesHut::ComputeMotion() {
    spdlog::info("Computing Motion forces");
    for (int i = 0; i < this->bodies.size(); i++) {
        spdlog::info("Computing forces for {}", bodies[i].get_name());
        Traverse(bodies[i], *(this->root));
        UpdateVelocity(bodies[i]);
        UpdatePosition(bodies[i]);
    }
}

void BarnesHut::Traverse(Body &body, Box &box) {
    spdlog::info("Traversing tree body : {}", body.get_name());
    if (body.get_name().compare("Sun") == 0) {
        spdlog::info("Body is the Sun, skipping");
        return;
    }

    if (box.get_box_type() == BOX_TYPE::INTERNAL && Threshold(body, box.get_center_of_mass(), box.get_dimensions())) {
        spdlog::debug("Internal node, computing acceleration");
        ComputeAcceleration(body, box.get_total_mass(), box.get_center_of_mass());
        return;
    }


    if ((box.get_box_type() == BOX_TYPE::LEAF
         && box.get_body() != nullptr) && (box.get_body()->get_name().compare(body.get_name()) != 0)) {
        spdlog::debug("Leaf node, computing acceleration");
        ComputeAcceleration(body, box.get_total_mass(), box.get_center_of_mass());
        return;
    }


    for (int i = 0; i < box.get_sub_boxes().size(); i++) {
        Traverse(body, box.get_sub_boxes()[i]);
    }
}

bool BarnesHut::Threshold(Body body, PositionVector center_of_mass, Dimension dim) {
    PositionVector temp = body.get_position() - center_of_mass;
    double th = sqrt(pow(temp.get_x(), 2) + pow(temp.get_y(), 2) + pow(temp.get_z(), 2)) / (2 * dim.get_length());

    if (th <= this->threshold) true;
    return false;
}

void BarnesHut::ComputeAcceleration(Body &body1, double mass, PositionVector r2) {
    spdlog::debug("Computing acceleration for : {}", body1.get_name());
    double scalar = (this->G * mass);
    spdlog::debug("Scalar resolved : {}", scalar);
    PositionVector relat_dist = r2 - body1.get_position();
    spdlog::debug("Relative distance : [{0}, {1}, {2}]", relat_dist.get_x(), relat_dist.get_y(), relat_dist.get_z());
    scalar /= pow((pow(relat_dist.get_x(), 2) + pow(relat_dist.get_y(), 2) + pow(relat_dist.get_z(), 2) +
                   pow(this->epsilon, 2)), 1.5);
    PositionVector acceleration = relat_dist * scalar;
    spdlog::debug("Acceleration : [{0}, {1}, {2}]", acceleration.get_x(), acceleration.get_y(), acceleration.get_z());
    body1.set_acceleration(acceleration);
}

void BarnesHut::UpdateVelocity(Body &body) {
    body.set_velocity(body.get_accerleration() * this->delta / 2);
}

void BarnesHut::UpdatePosition(Body &body) {
    body.set_position(body.get_velocity() * this->delta / 2);
}

void BarnesHut::DisplayTree() {
    DisplayBox(*(this->root));
}

void BarnesHut::DisplayBox(Box box) {
    box.DisplayBox();
    for (int i = 0; i < box.get_sub_boxes().size(); i++) {
        this->DisplayBox(box.get_sub_boxes()[i]);
    }
}

void BarnesHut::CreateVtkFile() {
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    AddPoint(points, root);
    vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
    // Set the points to the polydata object
    polydata->SetPoints(points);

    vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetRadius(1.0); // Adjust the radius as needed
    sphereSource->SetThetaResolution(16); // Adjust the resolution as needed
    sphereSource->SetPhiResolution(16);

    vtkSmartPointer<vtkGlyph3D> glyphFilter = vtkSmartPointer<vtkGlyph3D>::New();
    glyphFilter->SetSourceConnection(sphereSource->GetOutputPort());
    glyphFilter->SetInputData(polydata);
    glyphFilter->SetScaleModeToDataScalingOff(); // Use the same size for all spheres
    glyphFilter->Update();

    // Write the output to a .vtp file
    vtkSmartPointer<vtkXMLPolyDataWriter> writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
    writer->SetFileName("../data/spheres.vtp");
    writer->SetInputData(glyphFilter->GetOutput());
    writer->Write();

//    // Write the polydata to a .vtk file
//    vtkSmartPointer<vtkPolyDataWriter> writer = vtkSmartPointer<vtkPolyDataWriter>::New();
//    writer->SetFileName("../data/points.vtp");
//    writer->SetInputData(polydata);
//    writer->Write();
}

void BarnesHut::AddPoint(const vtkSmartPointer<vtkPoints> &points, Box *box) {
    if (box->get_body() != nullptr) {
        points->InsertNextPoint(box->get_body()->get_position().get_x()/100,
                                box->get_body()->get_position().get_y()/100, box->get_body()->get_position().get_z()/100);
    }
    for (auto subBox: box->get_sub_boxes()) {
        AddPoint(points, &subBox);
    }
}