#include "sfml_controller.hpp"


SFML_controller::SFML_controller(std::shared_ptr<Model> model, const sf::Color& col) :
    model(model),
    background_color(col),
    window(sf::VideoMode(800, 600), "SFML window")
{
    update_all_representations();
    update_and_draw();
}

#include <iostream>
void SFML_controller::update_all_representations()
{
    model->update();
    model->empty_last_elements();
    modified = model->get_all_elements();
    update_comp_in_drawing = false;
    std::cout<<modified.size()<<std::endl;
    update_components();
}

void SFML_controller::update_and_draw()
{
    if(update_comp_in_drawing)
    {
        model->update();
        modified = model->get_updated();
        update_components();
    }
    else
        update_comp_in_drawing = true;

    sf::Event event;
    while(window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            window.close();
        else if(event.type == sf::Event::KeyPressed)
            if(event.key.code == sf::Keyboard::Escape)
                update_all_representations();
    }
    std::cout<<"LAUNCHING"<<std::endl;

    window.clear(background_color);
    for(auto view : views)
    {
        std::cout<<"View"<<std::endl;
        view->draw();
    }
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(0,0),sf::Color::Red),
        sf::Vertex(sf::Vector2f(800,600),sf::Color::Red)
    };
    window.draw(line,2,sf::Lines);
    window.display();
}

bool SFML_controller::is_alive()
{return window.isOpen();}

void SFML_controller::add_view(std::shared_ptr<SFML_view> view)
{
    if(view)
    {
        view->set_window(&window);
        views.push_back(view);
    }
}

void SFML_controller::update_components()
{
    for(auto view : views)
        view->update(modified);
}
