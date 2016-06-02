#ifndef CAMERA_MODEL_HPP
#define CAMERA_MODEL_HPP


#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <cmath>

#include "model.hpp"


class Camera_model
{
    public:
        Camera_model(double w, double h);

        glm::vec3 get_transformed(const glm::vec3& point) const;

        void update_angles_matrix(int dif_x, int dif_y);
        void update_position_matrix(int dif_x, int dif_y);
        void update_x_offset(int x);
        void update_y_offset(int y);
        void update_scale_factor(double r);

        void set_callback(std::function<void()> callback);

    private:
        double w_window, h_window;
        double theta_speed, phi_speed, camera_speed;
        double scale_factor, theta, phi;
        glm::mat4 projection_matrix, look_at_matrix, model_matrix;
        glm::vec3 camera_origin, camera_direction, camera_up;

        std::function<void()> to_call_when_updated;

        void apply_cur_transformation();
        void update_camera_direction();
        void update_look_at_matrix();
};

#endif
