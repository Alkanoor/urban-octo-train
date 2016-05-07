#include "controller.hpp"
#include "model.hpp"


class SFML_controller : public Controller
{
    public:
        SFML_controller(std::shared_ptr<Model> model);

        void update_all_representations(bool update_comp = true);
        void update_and_draw();
        bool is_alive();

        void add_view(std::shared_ptr<SFML_view> view);

    private:
        std::shared_ptr<Model> model;
        std::vector<std::shared_ptr<SFML_view> > views;

        void update_components();
};
