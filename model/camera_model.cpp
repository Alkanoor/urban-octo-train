#include "camera_model.hpp"


Camera_model::Camera_model(double w, double h) :
    w_window(w),
    h_window(h),
    theta_speed(0.01),
    phi_speed(0.01),
    camera_speed(10.),
    scale_factor(1.),
    theta(M_PI/4.),
    phi(M_PI/4.),
    camera_origin(500,500,500),
    camera_up(0,0,-1)
{
    projection_matrix = glm::perspective(70.0f,4.0f/3.0f,0.1f,100.0f);
    //projection_matrix = glm::ortho(-1.f,1.f,-1.f,1.f,-1.f,1.f);
    update_camera_direction();
    update_look_at_matrix();
}

glm::vec3 Camera_model::get_transformed(const glm::vec3& point) const
{
    glm::vec4 transformed = projection_matrix*look_at_matrix*glm::vec4(point.x,point.y,point.z,1.0);
    return glm::vec3(transformed.x/transformed.w*w_window/2.*scale_factor,transformed.y/transformed.w*h_window/2*scale_factor,transformed.z);
}

void Camera_model::update_angles_matrix(int dif_x, int dif_y)
{
    if(theta+dif_y*theta_speed>=-M_PI/2.+0.00001&&theta+dif_y*theta_speed<=M_PI/2.-0.00001)
        theta += dif_y*theta_speed;
    phi += dif_x*phi_speed;
    update_camera_direction();
    update_look_at_matrix();
    if(to_call_when_updated)
        to_call_when_updated();
}

void Camera_model::update_position_matrix(int dif_x, int dif_y)
{
    camera_origin += glm::normalize(glm::cross(camera_direction, camera_up))*(float)(camera_speed*dif_x);
    camera_origin += camera_direction*(float)(camera_speed*dif_y);

    update_look_at_matrix();
    if(to_call_when_updated)
        to_call_when_updated();
}

void Camera_model::update_x_offset(int x)
{
    camera_origin = glm::normalize(glm::cross(camera_direction, camera_up))*(float)(camera_speed*x);

    update_look_at_matrix();
    if(to_call_when_updated)
        to_call_when_updated();
}

void Camera_model::update_y_offset(int y)
{
    camera_origin = camera_direction*(float)(camera_speed*y);

    update_look_at_matrix();
    if(to_call_when_updated)
        to_call_when_updated();
}

void Camera_model::update_scale_factor(double r)
{
    scale_factor = exp(0.75*log(r+1.))/30.;
    if(to_call_when_updated)
        to_call_when_updated();
}

void Camera_model::set_callback(std::function<void()> callback)
{
    to_call_when_updated = callback;
    callback();
}

void Camera_model::update_camera_direction()
{
    double x = -cos(theta)*cos(phi);
    double y = -cos(theta)*sin(phi);
    double z = -sin(theta);
    camera_direction = glm::normalize(glm::vec3(x,y,z));
}

void Camera_model::update_look_at_matrix()
{
    look_at_matrix = glm::lookAt(camera_origin,camera_origin+camera_direction,camera_up);
}
