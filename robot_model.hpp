#ifndef ROBOT_MODEL_HPP
#define ROBOT_MODEL_HPP


#include "camera_model.hpp"
#include "model.hpp"


class Robot_model : public Model
{
    public:
        Robot_model(int n, std::shared_ptr<Camera_model> camera = std::shared_ptr<Camera_model>());
        Robot_model(double body_radius=50, double leg_length=100, double foot_length=100, double body_to_leg_angle=120., double leg_angle=0., double leg_to_foot_angle=30., int n=6, std::shared_ptr<Camera_model> camera = std::shared_ptr<Camera_model>());

        void update_body_to_leg_angles(const std::vector<double>& angles);
        void update_leg_angles(const std::vector<double>& angles);
        void update_leg_to_foot_angles(const std::vector<double>& angles);

        void update_();
        void update_element(const std::string& name, Element& elem);
        void update_parameter(const std::string& name, const std::string& param_name, double val);

        void update_for_view();

    private:
        int N;
        std::vector<glm::vec3> foots;

        double offset_x, offset_y, offset_z;
        double lowest_point_body_angle, body_angle;
        double body_radius, leg_length, foot_length;
        std::vector<double> body_to_leg_angles, leg_angles, leg_to_foot_angles;

        std::shared_ptr<Camera_model> camera;
};

#endif
