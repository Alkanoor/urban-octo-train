#include "opengl_controller.hpp"


int main()
{
    std::shared_ptr<Model> model(new Robot_model());
    Controller::add_controller(std::shared_ptr<Controller>(new Opengl_controller(model)));

    while(Controller::is_controller_alive())
        Controller::update_and_draw();

    return 0;
}
