#include "controller.hpp"


std::vector<std::shared_ptr<Controller> > Controller::controllers;

void Controller::update_and_draw()
{}

bool Controller::is_alive()
{return false;}

void Controller::add_controller(std::shared_ptr<Controller> c)
{controllers.push_back(c);}

bool Controller::is_controller_alive()
{
    for(auto c : controllers)
        if(c&&c->is_alive())
            return true;
    return false;
}

void Controller::update_and_draw_all()
{
    for(auto c : controllers)
        if(c)
            c->update_and_draw();
}
