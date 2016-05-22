#include "sfml_controller.hpp"
#include "robot_model.hpp"
#include "sfml_view.hpp"


int main()
{
    std::shared_ptr<Camera_model> camera_model(new Camera_model(1200,900));
    std::shared_ptr<Robot_model> model(new Robot_model(6,camera_model));
    std::shared_ptr<SFML_controller> controller(new SFML_controller(model));

    camera_model->set_callback(std::bind(&Robot_model::update_for_view,model));
    controller->add_view(std::shared_ptr<SFML_view>(new SFML_view(sf::FloatRect(-600, -450, 1200, 900),sf::FloatRect(0, 0, 1, 1))));
    controller->set_mouse_callback(std::bind(&Camera_model::update_angles_matrix,camera_model,std::placeholders::_1,std::placeholders::_2));
    controller->set_move_callback(std::bind(&Camera_model::update_position_matrix,camera_model,std::placeholders::_1,std::placeholders::_2));
    controller->set_scale_callback(std::bind(&Camera_model::update_scale_factor,camera_model,std::placeholders::_1));
    Controller::add_controller(controller);

    while(Controller::is_controller_alive())
        Controller::update_and_draw_all();

    return 0;
}
