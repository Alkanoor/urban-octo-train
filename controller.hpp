#include "view.hpp"


class Controller
{
    public:
        virtual void update_and_draw();
        virtual bool is_alive();

        static void add_controller(std::shared_ptr<Controller> c);
        static bool is_controller_alive();

    private:
        std::vector<std::shared_ptr<Controller> > controllers;
};
