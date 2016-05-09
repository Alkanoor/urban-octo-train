#include <SFML/Graphics.hpp>

#include "union_find.hpp"
#include "view.hpp"


class SFML_view
{
    public:
        SFML_view(int type);
        SFML_view(int type, const sf::FloatRect& rect, const sf::FloatRect& viewport);

        void set_window(sf::Window* window);

        void draw();
        void update(std::map<std::string,Element>& elements);

    private:
        int type;

        sf::View view;
        sf::Window* window;

        std::vector<sf::Vertex> lines;
        std::vector<std::shared_ptr<sf::Shape> > shapes;

        sf::Color foot_color;
        sf::Color knee_color;
        sf::Color hip_color;
        sf::Color wire_color;
};
