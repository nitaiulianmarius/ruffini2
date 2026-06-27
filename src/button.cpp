#include<iostream>

#include"button.h"

namespace bt
{

void Button::update(sf::RenderWindow* window,std::vector<stateMachine*>& currentState)
{
    (void)currentState;
    sf::Vector2i mouseCoordinate = sf::Mouse::getPosition(*window);
    int x1, y1;

    x1 = mouseCoordinate.x;
    y1 = mouseCoordinate.y;

    if (x < x1 && x1 < x + width && y < y1 && y1 < y + height)
    {
        color = sf::Color::Red;
            state = BUTTON_PRESSED_STATE;
    }

    else
    {
        color = sf::Color::White;
            state = BUTTON_NORMAL_STATE;
    }
    text.setPosition(x, y);
}

void Button::render(sf::RenderWindow*& window)
{
    if(state == BUTTON_PRESSED_STATE)
    {
        sf::RectangleShape rectangle(sf::Vector2f(width,height));
        rectangle.setPosition(x,y);
        rectangle.setFillColor(sf::Color(0,0,0,20));
        window->draw(rectangle);
    }


    text.setFillColor(color);
    window->draw(text);
}

} //namespace
