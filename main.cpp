#include "controller/sfml_controller.hpp"
#include "model/robot_model.hpp"
#include "view/sfml_view.hpp"

#include "utils/linear_algebra.hpp"


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
    controller->set_time_callback(std::bind(&Robot_model::update_time,model,std::placeholders::_1));
    Controller::add_controller(controller);

    Leg temp_leg(6,Leg_angles(0,150.,10.,70.));
    for(int i=0;i<6;i++)
        temp_leg[i].body_angle = (float)(i)/(float)(6)*2.*M_PI;
    model->add_step(temp_leg, 1000);

    Plan p(glm::vec3(1,0,0), glm::vec3(0,1,0), glm::vec3(-1,-1,1));

    for(int i=0;i<6;i++)
    {
        if(!(i%2))
        {
            temp_leg[i].body_to_leg_angle = 100.;
            temp_leg[i].leg_angle = -20.;
            temp_leg[i].leg_to_foot_angle = 30.;
        }
        else
        {
            temp_leg[i].body_to_leg_angle = 120.;
            temp_leg[i].leg_angle = -10.;
            temp_leg[i].leg_to_foot_angle = 50.;
        }
    }
    model->add_step(temp_leg, 1000);

    while(Controller::is_controller_alive())
        Controller::update_and_draw_all();

    return 0;
}
