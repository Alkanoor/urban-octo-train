#include "sfml_controller.hpp"
#include "robot_model.hpp"
#include "sfml_view.hpp"


int main()
{
    std::shared_ptr<Model> model(new Robot_model());
    std::shared_ptr<SFML_controller> controller(new SFML_controller(model));
    controller->add_view(std::shared_ptr<SFML_view>(new SFML_view(0)));
    Controller::add_controller(controller);

    while(Controller::is_controller_alive())
        Controller::update_and_draw_all();

    return 0;
}
