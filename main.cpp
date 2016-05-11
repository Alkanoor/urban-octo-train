#include "sfml_controller.hpp"
#include "robot_model.hpp"
#include "sfml_view.hpp"


int main()
{
    std::shared_ptr<Robot_model> model(new Robot_model());
    std::shared_ptr<SFML_controller> controller(new SFML_controller(model));
    controller->add_view(std::shared_ptr<SFML_view>(new SFML_view(0)));
    controller->set_mouse_callback(std::bind(&Robot_model::update_angles_matrix,model,std::placeholders::_1,std::placeholders::_2,true));
    Controller::add_controller(controller);

    while(Controller::is_controller_alive())
        Controller::update_and_draw_all();

    return 0;
}
