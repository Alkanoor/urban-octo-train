#include "sfml_view.hpp"


SFML_view::SFML_view(int type) :
    type(type),
    window(nullptr)
{}

SFML_view::SFML_view(int type, const sf::FloatRect& rect, const sf::FloatRect& viewport) :
    type(type),
    window(nullptr)
{
    view.reset(rect);
    view.setViewport(viewport);
}

void SFML_view::set_window(sf::Window* window)
{
    this->window = window;
}

void SFML_view::draw()
{
    for(auto line : lines)
        if(window)
            window->draw(line,2,sf::Lines);
    for(auto shape : shapes)
        if(window)
            window->draw(shape);
}

void SFML_view::update(std::map<std::string,Element>& elements)
{
    int n = elements["N"];
    lines.resize(n*3);
    shapes.resize(n*3);
    for(int i=0;i<n;i++)
    {
        std::string pos1 = "foot"+(char)i;
        if(elements.count(pos1))
        {
            Element el1 = elements[pos1];
            Element el2 = elements["knee"+(char)i];
            Element el3 = elements["hip"+(char)i];

            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(10, 10)),
                sf::Vertex(sf::Vector2f(150, 150))
            };
        }
    }
}
