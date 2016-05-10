#ifndef SFML_VIEW_2_HPP
#define SFML_VIEW_2_HPP


#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "view.hpp"


class SFML_view : public View
{
    public:
        SFML_view(int type = 1);
        SFML_view(int type, const sf::FloatRect& rect, const sf::FloatRect& viewport);

        void set_window(sf::RenderWindow* window);

        void draw();
        void update(const std::map<std::string,Element>& elements);

    private:
        int type;

        sf::View view;
        sf::RenderWindow* window;
        bool reset_view;

        std::vector<sf::Vertex> lines;
        std::vector<std::shared_ptr<sf::Shape> > shapes;

        sf::Color foot_color;
        sf::Color knee_color;
        sf::Color hip_color;
        sf::Color wire_color;
        sf::Color background_color;
};

#endif
