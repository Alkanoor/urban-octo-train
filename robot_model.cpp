#include "robot_model.hpp"


#include <iostream>
Robot_model::Robot_model(int n, std::shared_ptr<Camera_model> cam) :
    Robot_model(50,75,100,150.,20.,30.,n,cam)
{}

Robot_model::Robot_model(double body_radius, double leg_length, double foot_length, double body_to_leg_angle, double leg_angle, double leg_to_foot_angle, int n, std::shared_ptr<Camera_model> cam) :
    N((n>256)?256:((n<3)?4:n+1)),
    offset_x(0),
    offset_y(0),
    offset_z(0),
    lowest_point_body_angle(0),
    body_angle(0),
    body_radius(body_radius),
    leg_length(leg_length),
    foot_length(foot_length),
    body_to_leg_angles(N,body_to_leg_angle),
    leg_angles(N,leg_angle),
    leg_to_foot_angles(N,leg_to_foot_angle),
    camera(cam)
{}

void update_time(int t)
{
    int time = 0;
    int i=0;
    for(;i<millis_time_periods.size()&&t>time;i++)
        if(millis_time_periods[i])
            time += millis_time_periods[i];

    if(i<millis_time_periods.size())
        update_
    std::vector<Legs> steps;
}

void Robot_model::update_()
{
    elements.modify("N",Element("val",N));
    std::cout<<"Update elements with "<<N<<std::endl;

    foots.resize(3*N);
    for(int i=0;i<N;i++)
    {
        double theta = (float)(i)/(float)(N-1)*2.*M_PI;
        double dir2_x = cos(leg_angles[i]/180.*M_PI+theta);
        double dir2_y = sin(leg_angles[i]/180.*M_PI+theta);
        double beta = body_to_leg_angles[i]/180.*M_PI;
        double gamma = leg_to_foot_angles[i]/180.*M_PI;
        foots[3*i+2] = glm::vec3(cos(theta)*body_radius,sin(theta)*body_radius,0);
        foots[3*i+1] = foots[3*i+2]+glm::vec3(-leg_length*dir2_x*cos(beta),-leg_length*dir2_y*cos(beta),leg_length*sin(beta));
        foots[3*i] = foots[3*i+1]+glm::vec3(foot_length*dir2_x*cos(gamma),foot_length*dir2_y*cos(gamma),-foot_length*sin(gamma));
    }

    /*float scale = 100;
    float offX = 0, offY = 0, offZ = 0;
    foots.resize(3*N);
    std::map<std::string,double> coords;
    for(int i=0;i<N;i++)
    {
        double angle = (float)(i)/(float)(N-1)*2.*M_PI;
        double r = 3;
        coords["x"] = cos(angle)*r*scale+offX;
        coords["y"] = sin(angle)*r*scale+offY;
        coords["z"] = 0*scale+offZ;
        std::cout<<coords["x"]<<" "<<coords["y"]<<" "<<coords["z"]<<std::endl;
        foots[3*i] = Element(coords);
        r = 1.5;
        coords["x"] = cos(angle)*r*scale+offX;
        coords["y"] = sin(angle)*r*scale+offY;
        coords["z"] = 4*scale+offZ;
        std::cout<<coords["x"]<<" "<<coords["y"]<<" "<<coords["z"]<<std::endl;
        foots[3*i+1] = Element(coords);
        r = 1.;
        coords["x"] = cos(angle)*r*scale+offX;
        coords["y"] = sin(angle)*r*scale+offY;
        coords["z"] = 3*scale+offZ;
        std::cout<<coords["x"]<<" "<<coords["y"]<<" "<<coords["z"]<<std::endl;
        foots[3*i+2] = Element(coords);
    }*/

    update_for_view();
}

void Robot_model::update_element(const std::string& name, Element& elem)
{}

void Robot_model::update_parameter(const std::string& name, const std::string& param_name, double val)
{}

/*void Robot_model::update_global_parameters()
{
    glm::vec3 gravity_center = ;
    lowest_point_body_angle = ;
    body_angle = ;
    std::vector<glm::vec3> lowest_points = ;
    if(lowest_points != previous_lowest_points)
}*/

void Robot_model::update_for_view()
{
    if(!camera)
        return;

    std::map<std::string,double> coords;
    for(unsigned int i=0;i<foots.size();i++)
    {
        glm::vec3 transformed = camera->get_transformed(foots[i]);
        coords["x"] = transformed.x;
        coords["y"] = transformed.y;
        std::string suffix;
        suffix += (char)(i/3+'0');
        if(!(i%3))
            elements.modify("foot"+suffix,Element(coords));
        else if(i%3==1)
            elements.modify("knee"+suffix,Element(coords));
        else
            elements.modify("hip"+suffix,Element(coords));
    }

    update_views();
}
