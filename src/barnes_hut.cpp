#include "barnes_hut.hpp"

BarnesHut::BarnesHut(vector<Body> bodies) {
    this->bodies = bodies;
    this->root = nullptr;
}

void BarnesHut::ClearOctTree() {
    spdlog::info("Clearing Oct tree");
    ClearBox(this->root);
}

void BarnesHut::ClearBox(Box *box){
    if(box->get_sub_boxes().size() == 0) { delete box; return; }

    for(auto sub_box = box->get_sub_boxes().begin(); sub_box != box->get_sub_boxes().end(); sub_box++){
        if(sub_box != nullptr) ClearBox(sub_box);
    }
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

void BarnesHut::UpdateInitialVelocity(){
    PositionVector momentum(0, 0, 0);
    double total_mass = 0;
    for(auto &body: bodies) {
        momentum += body.get_velocity()*body.get_mass();
        total_mass += body.get_mass();
    }

    for(auto &body: bodies){
        body.set_velocity((momentum - body.get_velocity()*body.get_mass())/(total_mass - body.get_mass()));
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
    double th = EuclideanDistance(body.get_position(), center_of_mass) / (2 * dim.get_length());

    if (th <= this->threshold) true;
    return false;
}

void BarnesHut::ComputeAcceleration(Body &body1, double mass, PositionVector r2) {
    spdlog::debug("Computing acceleration for : {}", body1.get_name());
    
    double scalar = (this->G * mass);
    scalar /= pow(pow(EuclideanDistance(r2, body1.get_position()), 2) +  pow(this->epsilon, 2), 1.5);
    spdlog::info("Scalar resolved : {}", scalar);
    
    PositionVector relat_dist = r2 - body1.get_position();
    PositionVector acceleration = relat_dist * scalar;
    body1.update_acceleration(acceleration);
    spdlog::info("Acceleration : [{0}, {1}, {2}]", body1.get_accerleration().get_x(), body1.get_accerleration().get_y(), body1.get_accerleration().get_z());
}

void BarnesHut::UpdateVelocity(Body &body) {
    body.update_velocity(body.get_accerleration() * this->delta );
}

void BarnesHut::UpdatePosition(Body &body) {
    body.update_position(body.get_velocity() * this->delta );
}

void BarnesHut::Display() {
    for(auto body: bodies){
        spdlog::info("Body name: {}", body.get_name());
        spdlog::info("Position: [{0} {1} {2}]", body.get_position().get_x(), body.get_position().get_y(), body.get_position().get_z());
        spdlog::info("Velocity: [{0} {1} {2}]", body.get_velocity().get_x(), body.get_velocity().get_y(), body.get_velocity().get_z());
        spdlog::info("Acceleration: [{0} {1} {2}]", body.get_accerleration().get_x(), body.get_accerleration().get_y(), body.get_accerleration().get_z());
    }

    spdlog::info("KE of the system: {}", this->KE);
    spdlog::info("PE of the system: {}", this->PE);
    double viral = (this->KE*2)/abs(this->PE);
    spdlog::info("Viral Eq of the system: {}", viral);
}

void BarnesHut::CreateVtkFile() {
    vtkNew<vtkPoints> points;

    for(auto body: bodies){
        points->InsertNextPoint(
            body.get_position().get_x(), body.get_position().get_y(), body.get_position().get_z()
        );
    }    

    vtkNew<vtkPolyData> polydata;
    polydata->SetPoints(points);
    vtkNew<vtkXMLPolyDataWriter> writer;
    writer->SetFileName("./data/test_.vtp");
    writer->SetInputData(polydata);
    writer->SetDataModeToAscii();
    writer->Write();
}

void BarnesHut::UpdateKE(){
    this->KE = 0;
    for(auto body: bodies){
        this->KE += 0.5*(body.get_mass()*pow(EuclideanDistance(body.get_velocity(), PositionVector()), 2));
    }
}

void BarnesHut::UpdatePE(){
    this->PE = 0;

    for(int i = 0; i < bodies.size(); i++){
        for(int j = i+1; j < bodies.size(); j++){
            this->PE -= this->G*(bodies[i].get_mass()*bodies[j].get_mass());
            this->PE /= EuclideanDistance(bodies[i].get_position(), bodies[j].get_position());
        }
    }
}


double BarnesHut::EuclideanDistance(PositionVector r1, PositionVector r2){
    PositionVector rel = r1 - r2;
    return sqrt(pow(rel.get_x(), 2) + pow(rel.get_y(), 2) + pow(rel.get_z(), 2));
}