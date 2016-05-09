#include "sfml_controller.hpp"


SFML_controller::SFML_controller(std::shared_ptr<Model> model, const sf::Color& col) :
    model(model),
    background_color(col),
    window(sf::VideoMode(800, 600), "SFML window")
{
    update_all_representations();
    update_and_draw();
}

void SFML_controller::update_all_representations()
{
    update_comp_in_drawing = false;
    modified = model->get_all_elements();
    model->empty_last_elements();
    update_components();
}

void SFML_controller::update_and_draw()
{
    if(update_comp_in_drawing)
    {
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

    window.clear(background_color);
    for(auto view : views)
        view->draw();
    window.display();
}

bool SFML_controller::is_alive()
{return window.isOpen();}

void SFML_controller::add_view(std::shared_ptr<SFML_view> view)
{views.push_back(view);}

void SFML_controller::update_components()
{
    for(auto view : views)
        view->update(modified);
}
