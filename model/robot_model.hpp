#ifndef ROBOT_MODEL_HPP
#define ROBOT_MODEL_HPP


#include "camera_model.hpp"
#include "model.hpp"


class Leg_angles
{
    public:
        Leg_angles(double a, double b, double c, double d) :
            body_angle(a),
            body_to_leg_angle(b),
            leg_angle(c),
            leg_to_foot_angle(d)
        {}

        double body_angle;
        double body_to_leg_angle;
        double leg_angle;
        double leg_to_foot_angle;
};

typedef std::vector<Leg_angles> Leg;

class Robot_model : public Model
{
    public:
        Robot_model(int n, std::shared_ptr<Camera_model> camera = std::shared_ptr<Camera_model>());
        Robot_model(double body_radius=50, double leg_length=100, double foot_length=100, double body_to_leg_angle=120., double leg_angle=0., double leg_to_foot_angle=30., int n=6, std::shared_ptr<Camera_model> camera = std::shared_ptr<Camera_model>());

        void update_time(int t);
        void add_step(const Leg& l, int millis_delay);

        void update_body_to_leg_angles(const std::vector<double>& angles);
        void update_leg_angles(const std::vector<double>& angles);
        void update_leg_to_foot_angles(const std::vector<double>& angles);

        void update_();
        void update_element(const std::string& name, Element& elem);
        void update_parameter(const std::string& name, const std::string& param_name, double val);

        void update_for_view();

        void set_current_leg_as_template(double body_to_leg_angle=120., double leg_angle=0., double leg_to_foot_angle=30., int n=6);

    private:
        int N;
        std::vector<glm::vec3> foots;

        double offset_x, offset_y, offset_z;
        double lowest_point_body_angle, body_angle;
        double body_radius, leg_length, foot_length;
        Leg current_leg;

        std::shared_ptr<Camera_model> camera;

        std::vector<int> millis_time_periods;
        std::vector<Leg> steps;
        int total_time;

        std::array<glm::vec3,3> compute_relative_positions(const Leg_angles& leg);
        void update_global_parameters(const Leg& leg1, const Leg& leg2, double ratio);
        void find_coplanar_points(const std::vector<glm::vec3>& current_foots);
};

#endif
