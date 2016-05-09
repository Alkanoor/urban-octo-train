#ifndef OPENGL_CONTROLLER_HPP
#define OPENGL_CONTROLLER_HPP


#include "controller.hpp"
#include "model.hpp"


class Opengl_controller : public Controller
{
    public:
        Opengl_controller(std::shared_ptr<Model> model);

        void update_and_draw();
};

#endif
