#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP


#include <memory>
#include <vector>

#include "../view/view.hpp"


class Controller
{
    public:
        virtual void update_and_draw();
        virtual bool is_alive();

        static void add_controller(std::shared_ptr<Controller> c);
        static bool is_controller_alive();
        static void update_and_draw_all();

    private:
        static std::vector<std::shared_ptr<Controller> > controllers;
};

#endif
