#include "sfml_view.hpp"


SFML_view::SFML_view(int type) :
    type(type),
    window(nullptr),
    foot_color(sf::Color::Green),
    knee_color(sf::Color::Blue),
    hip_color(sf::Color::Red),
    wire_color(sf::Color::Black)
{}

SFML_view::SFML_view(int type, const sf::FloatRect& rect, const sf::FloatRect& viewport) :
    type(type),
    window(nullptr),
    foot_color(sf::Color::Green),
    knee_color(sf::Color::Blue),
    hip_color(sf::Color::Red),
    wire_color(sf::Color::Black)
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
    if(window)
        window->setView(view);
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
    std::vector<Point> all_hips(n);
    for(int i=0;i<n;i++)
    {
        std::string pos1 = "foot"+(char)(i+'0');
        if(elements.count(pos1))
        {
            Element el1 = elements[pos1];
            Element el2 = elements["knee"+(char)(i+'0')];
            Element el3 = elements["hip"+(char)(i+'0')];

            int x1, y1, x2, y2, x3, y3;

            if(type==1)
            {
                x1 = el1["x"];
                y1 = el1["y"];
                x2 = el2["x"];
                y2 = el2["y"];
                x3 = el3["x"];
                y3 = el3["y"];
            }
            else
            {
                x1 = el1["x"];
                y1 = el1["z"];
                x2 = el2["x"];
                y2 = el2["z"];
                x3 = el3["x"];
                y3 = el3["z"];
            }

            sf::CircleShape shape(2);
            shape.setFillColor(foot_color);
            shape.setCenter(x1,y1);
            shapes[3*i] = shape;
            shape.resize(3);
            shape.setFillColor(knee_color);
            shape.setCenter(x2,y2);
            shapes[3*i+1] = shape;
            shape.resize(4);
            shape.setFillColor(hip_color);
            shape.setCenter(x3,y3);
            shapes[3*i+2] = shape;

            lines[6*i] = sf::Vertex(sf::Vector2f(x1,y1),wire_color);
            lines[6*i+1] = sf::Vertex(sf::Vector2f(x2,y2),wire_color);
            lines[6*i+2] = sf::Vertex(sf::Vector2f(x2,y2),wire_color);
            lines[6*i+3] = sf::Vertex(sf::Vector2f(x3,y3),wire_color);

            all_hips.push_back(Point(x3,y3));
        }
        else
            all_hips.push_back(Point(shapes[3*i+2].getCenter().x,shapes[3*i+2].getCenter().y));
    }
    std::vector<Edge> minimized = minimum_spanning_tree(all_hips,true);
    for(unsigned int i=0;i<minimized.size()&&6*i+5<lines.size())
    {
        lines[6*i+4] = sf::Vertex(sf::Vector2f(minimized[i].first.first,minimized[i].first.second),wire_color);
        lines[6*i+5] = sf::Vertex(sf::Vector2f(minimized[i].second.first,minimized[i].second.second),wire_color);
    }
}
