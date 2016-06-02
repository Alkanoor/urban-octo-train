#include "sfml_controller.hpp"


SFML_controller::SFML_controller(std::shared_ptr<Model> model, const sf::Color& col) :
    model(model),
    background_color(col),
    window(sf::VideoMode(800, 600), "SFML window"),
    call_time(false),
    pressed_move(false),
    pressed_zoom(false)
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

    elapsed_time = clock.getElapsedTime();
    if(time_callback&&call_time)
        time_callback(elapsed_time.asMilliseconds());

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
            else if(event.key.code == sf::Keyboard::Up && move_callback)
                move_callback(0,1);
            else if(event.key.code == sf::Keyboard::Down && move_callback)
                move_callback(0,-1);
            else if(event.key.code == sf::Keyboard::Right && move_callback)
                move_callback(1,0);
            else if(event.key.code == sf::Keyboard::Left && move_callback)
                move_callback(-1,0);
            else if(event.key.code == sf::Keyboard::Return)
                clock.restart();
            else if(event.key.code == sf::Keyboard::S)
            {
                call_time = true;
                clock.restart();
            }
            else if(event.key.code == sf::Keyboard::T)
                call_time = false;
        }
        else if(event.type == sf::Event::MouseButtonPressed && !pressed_move && !pressed_zoom)
        {
            if(event.mouseButton.button==1)
            {
                prev_x = event.mouseButton.x;
                prev_y = event.mouseButton.y;
                pressed_zoom = true;
            }
            else
                if(!pressed_move)
                {
                    prev_x = event.mouseButton.x;
                    prev_y = event.mouseButton.y;
                    pressed_move = true;
                }
        }
        else if(event.type == sf::Event::MouseButtonReleased)
        {
            pressed_move = false;
            pressed_zoom = false;
        }
        else if(event.type == sf::Event::MouseMoved)
        {
            if(pressed_move&&mouse_callback)
            {
                mouse_callback(event.mouseMove.x-prev_x,event.mouseMove.y-prev_y);
                prev_x = event.mouseMove.x;
                prev_y = event.mouseMove.y;
            }
            else if(pressed_zoom&&scale_callback)
                scale_callback(sqrt((event.mouseMove.x-prev_x)*(event.mouseMove.x-prev_x)+(event.mouseMove.y-prev_y)*(event.mouseMove.y-prev_y)));
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

void SFML_controller::set_move_callback(std::function<void(int,int)> callback)
{move_callback = callback;}

void SFML_controller::set_scale_callback(std::function<void(float)> callback)
{scale_callback = callback;}

void SFML_controller::set_time_callback(std::function<void(int)> callback)
{time_callback = callback;}

void SFML_controller::update_components()
{
    for(auto view : views)
        view->update(modified);
}
