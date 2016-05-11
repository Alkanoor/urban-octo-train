#include "sfml_controller.hpp"


SFML_controller::SFML_controller(std::shared_ptr<Model> model, const sf::Color& col) :
    model(model),
    background_color(col),
    window(sf::VideoMode(800, 600), "SFML window"),
    pressed(false)
{
    update_all_representations();
    update_and_draw();
}

void SFML_controller::update_all_representations()
{
    model->update();
    model->empty_last_elements();
    modified = model->get_all_elements();
    update_comp_in_drawing = false;
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
        {
            if(event.key.code == sf::Keyboard::Escape)
                window.close();
            else if(event.key.code == sf::Keyboard::Space)
                update_all_representations();
        }
        else if(event.type == sf::Event::MouseButtonPressed)
        {
            if(!pressed)
            {
                prev_x = event.mouseButton.x;
                prev_y = event.mouseButton.y;
            }
            pressed = true;
        }
        else if(event.type == sf::Event::MouseButtonReleased)
            pressed = false;
        else if(event.type == sf::Event::MouseMoved)
            if(pressed&&mouse_callback)
            {
                mouse_callback(event.mouseMove.x-prev_x,event.mouseMove.y-prev_y);
                prev_x = event.mouseMove.x;
                prev_y = event.mouseMove.y;
            }
    }

    window.clear(background_color);
    for(auto view : views)
        view->draw();
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
        model->add_updatable(view);
    }
}

void SFML_controller::set_mouse_callback(std::function<void(int,int)> callback)
{mouse_callback = callback;}

void SFML_controller::update_components()
{
    for(auto view : views)
        view->update(modified);
}
