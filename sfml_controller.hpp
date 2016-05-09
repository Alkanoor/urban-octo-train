#ifndef SFML_CONTROLLER_HPP
#define SFML_CONTROLLER_HPP


#include "controller.hpp"
#include "sfml_view.hpp"
#include "model.hpp"


class SFML_controller : public Controller
{
    public:
        SFML_controller(std::shared_ptr<Model> model, const sf::Color& col = sf::Color::White);

        void update_all_representations();
        void update_and_draw(); //boolean which must be set to true if components of model should be recomputed before drawing
        bool is_alive();

        void add_view(std::shared_ptr<SFML_view> view);

    private:
        bool update_comp_in_drawing;
        std::map<std::string,Element> modified;

        std::shared_ptr<Model> model;
        std::vector<std::shared_ptr<SFML_view> > views;

        sf::Color background_color;
        sf::RenderWindow window;

        void update_components();
};

#endif
