#ifndef ROBOT_MODEL_HPP
#define ROBOT_MODEL_HPP


#include <cmath>

#include "model.hpp"


class Robot_model : public Model
{
    public:
        Robot_model(int n=6);

        void update_();
        void update_element(const std::string& name, Element& elem);
        void update_parameter(const std::string& name, const std::string& param_name, double val);

        void update_angles_matrix(int x, int y, bool modify_points = true);
        void update_x_offset(int x);
        void update_y_offset(int y);
        void update_scale_factor(double r);

    private:
        int N;
        std::vector<Element> foots;
        std::vector<Element> motor_angles;

        double theta_speed, phi_speed;
        double x_offset, y_offset, scale_factor, theta, phi;

        void apply_cur_transformation();
};

#endif
