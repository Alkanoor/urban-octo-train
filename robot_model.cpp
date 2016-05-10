#include "robot_model.hpp"


#include <iostream>
Robot_model::Robot_model(int n) :
    N((n>256)?256:((n<3)?3:n))
{}

void Robot_model::update_()
{
    elements.modify("N",Element("val",N));
    std::cout<<"Update elements with "<<N<<std::endl;

    float scale = 100;
    float offX = 400, offY = 300, offZ = 0;
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
    }

    for(int i=0;i<N;i++)
    {
        std::string suffix;
        suffix += (char)(i+'0');
        elements.modify("foot"+suffix,foots[3*i]);
        elements.modify("knee"+suffix,foots[3*i+1]);
        elements.modify("hip"+suffix,foots[3*i+2]);
    }
}

void Robot_model::update_element(const std::string& name, Element& elem)
{}

void Robot_model::update_parameter(const std::string& name, const std::string& param_name, double val)
{}
