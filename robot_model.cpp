#include "robot_model.hpp"


Robot_model::Robot_model(int n) :
    N((n>256)?256:((n<3)?3:n))
{}

void Robot_model::update_()
{
    elements.modify("N",Element("val",N));

    foots.resize(3*N);
    std::map<std::string,double> coords;
    for(int i=0;i<N;i++)
    {
        double angle = i/(N-1)*2*M_PI;
        double r = 3;
        coords["x"] = cos(angle)*r;
        coords["y"] = sin(angle)*r;
        coords["z"] = 0;
        foots[3*i] = Element(coords);
        r = 1.5;
        coords["x"] = cos(angle)*r;
        coords["y"] = sin(angle)*r;
        coords["z"] = 4;
        foots[3*i+1] = Element(coords);
        r = 1.;
        coords["x"] = cos(angle)*r;
        coords["y"] = sin(angle)*r;
        coords["z"] = 3;
        foots[3*i+2] = Element(coords);
    }

    for(int i=0;i<N;i++)
    {
        elements.modify("foot"+(char)(i+'0'),foots[3*i]);
        elements.modify("knee"+(char)(i+'0'),foots[3*i+1]);
        elements.modify("hip"+(char)(i+'0'),foots[3*i+2]);
    }
}

void Robot_model::update_element(const std::string& name, Element& elem)
{}

void Robot_model::update_parameter(const std::string& name, const std::string& param_name, double val)
{}
