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

    private:
        int N;
        std::vector<Element> foots;
        std::vector<Element> motor_angles;
};

#endif
