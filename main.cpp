#include "sfml_controller.hpp"
#include "robot_model.hpp"


int main()
{
    std::shared_ptr<Model> model(new Robot_model());
    Controller::add_controller(std::shared_ptr<Controller>(new SFML_controller(model)));

    while(Controller::is_controller_alive())
        Controller::update_and_draw_all();

    return 0;
}
