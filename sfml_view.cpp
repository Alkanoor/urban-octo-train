#include "union_find.hpp"
#include "sfml_view.hpp"


SFML_view::SFML_view() :
    window(nullptr),
    reset_view(true),
    N(-1),
    foot_color(sf::Color::Red),
    knee_color(sf::Color::Blue),
    hip_color(sf::Color::Green),
    wire_color(sf::Color::Black)
{}

SFML_view::SFML_view(const sf::FloatRect& rect, const sf::FloatRect& viewport) :
    window(nullptr),
    reset_view(false),
    N(-1),
    foot_color(sf::Color::Red),
    knee_color(sf::Color::Blue),
    hip_color(sf::Color::Green),
    wire_color(sf::Color::Black)
{
    view.reset(rect);
    view.setViewport(viewport);
}

void SFML_view::set_window(sf::RenderWindow* window)
{
    this->window = window;
    if(reset_view&&window)
        view = window->getView();
}

void SFML_view::draw()
{
    if(window)
        window->setView(view);
    if(window)
        window->draw(&(lines[0]),lines.size(),sf::Lines);
    for(auto shape : shapes)
        if(window&&shape)
            window->draw(*shape);
}

void SFML_view::update(const std::map<std::string,Element>& elements)
{
    if(N<1&&!elements.count("N"))
    {
        std::cerr<<"Warning, no N found in elements"<<std::endl;
        return;
    }
    else if(elements.count("N"))
        N = elements.find("N")->second["val"];

    float prev_x, prev_y, init_x, init_y;
    lines.resize(N*6);
    shapes.resize(N*3);
    std::vector<Point> all_hips(N);
    for(int i=0;i<N;i++)
    {
        std::string suffix;
        suffix += (char)(i+'0');
        if(elements.count("foot"+suffix))
        {
            Element el1 = elements.find("foot"+suffix)->second;
            Element el2 = elements.find("knee"+suffix)->second;
            Element el3 = elements.find("hip"+suffix)->second;

            double x1, y1, x2, y2, x3, y3;

            x1 = el1["x"];
            y1 = el1["y"];
            x2 = el2["x"];
            y2 = el2["y"];
            x3 = el3["x"];
            y3 = el3["y"];

            std::shared_ptr<sf::CircleShape> shape(new sf::CircleShape(3));
            shape->setOrigin(3,3);
            shape->setFillColor(foot_color);
            shape->setPosition(x1,y1);
            shapes[3*i] = shape;

            shape = std::shared_ptr<sf::CircleShape>(new sf::CircleShape(4));
            shape->setOrigin(4,4);
            shape->setFillColor(knee_color);
            shape->setPosition(x2,y2);
            shapes[3*i+1] = shape;

            shape = std::shared_ptr<sf::CircleShape>(new sf::CircleShape(5));
            shape->setOrigin(5,5);
            shape->setFillColor(hip_color);
            shape->setPosition(x3,y3);
            shapes[3*i+2] = shape;

            lines[6*i] = sf::Vertex(sf::Vector2f(x1,y1),wire_color);
            lines[6*i+1] = sf::Vertex(sf::Vector2f(x2,y2),wire_color);
            lines[6*i+2] = sf::Vertex(sf::Vector2f(x2,y2),wire_color);
            lines[6*i+3] = sf::Vertex(sf::Vector2f(x3,y3),wire_color);
            if(i>0)
            {
                lines[6*i+4] = sf::Vertex(sf::Vector2f(x3,y3),wire_color);
                lines[6*i+5] = sf::Vertex(sf::Vector2f(prev_x,prev_y),wire_color);
                prev_x = x3;
                prev_y = y3;
            }
            else
            {
                init_x = x3;
                init_y = y3;
                prev_x = x3;
                prev_y = y3;
            }

            all_hips[i] = Point(x3,y3);
        }
        else
            all_hips[i] = Point(shapes[3*i+2]->getPosition().x,shapes[3*i+2]->getPosition().y);
    }
    lines[4] = sf::Vertex(sf::Vector2f(init_x,init_y),wire_color);
    lines[5] = sf::Vertex(sf::Vector2f(prev_x,prev_y),wire_color);

    /*std::vector<Edge> minimized = minimum_spanning_tree(all_hips,true);
    for(unsigned int i=0;i<minimized.size()&&6*i+5<lines.size();i++)
    {
        lines[6*i+4] = sf::Vertex(sf::Vector2f(minimized[i].first.first,minimized[i].first.second),wire_color);
        lines[6*i+5] = sf::Vertex(sf::Vector2f(minimized[i].second.first,minimized[i].second.second),wire_color);
    }*/
}
