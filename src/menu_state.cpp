#include <fstream>
#include <iostream>
#include "menuState.h"
#include "playState.h"

void menuState::freeMemory()
{

}

void menuState::handleEvent(sf::RenderWindow* window,std::vector<stateMachine*>& currentState)
{
    while(window->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            window->close();

        if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            int numberOfButton = button.size();
            for(int i=0;i<numberOfButton;i++)
        if(button[i]->state == BUTTON_PRESSED_STATE)
                {
                    if(button[i]->mString == "Start game")
                        currentState.push_back(new playState(window));

                    if(button[i]->mString == "Story")
                        state = storyState;

                    if(button[i]->mString == "600x400")
                        window->create(sf::VideoMode(600, 400), "Ruffini v2", sf::Style::Close);

                    if(button[i]->mString == "720x640")
                        window->create(sf::VideoMode(720, 640), "Ruffini v2", sf::Style::Close);

                    if(button[i]->mString == "800x600")
                        window->create(sf::VideoMode(800, 600), "Ruffini v2", sf::Style::Close);

                    if(button[i]->mString == "1080x720")
                        window->create(sf::VideoMode(1080, 720), "Ruffini v2", sf::Style::Close);

                    if(button[i]->mString == "1280x720")
                        window->create(sf::VideoMode(1280, 720), "Ruffini v2", sf::Style::Close);

                    if(button[i]->mString == "1360x768")
                        window->create(sf::VideoMode(1360, 768), "Ruffini v2", sf::Style::Close);

                    if(button[i]->mString == "Quit")
                        window->close();

                    logoImage.setPosition(window->getSize().x/2-54, 0);
                    menuBackgroundSprite.setScale((float)window->getSize().x/menuBackgroundSprite.getLocalBounds().width, (float)window->getSize().y/menuBackgroundSprite.getLocalBounds().height);
                    story1Sprite.setScale((float)(window->getSize().x-140)/story1Sprite.getLocalBounds().width, (float)(window->getSize().y-100)/story1Sprite.getLocalBounds().height);
                    button[0]->y = window->getSize().y-40;
                    button[1]->y = window->getSize().y-40;
                    button[2]->y = window->getSize().y-40;
                    button[3]->x = window->getSize().x-60;
                    button[3]->y = window->getSize().y-40;
                }
        }
    }
}

void menuState::update(sf::RenderWindow* window,std::vector<stateMachine*>& currentState)
{
    _px = window->getSize().x / 20.;
    _py = window->getSize().y / 20.;

    int numberOfButton = button.size();
    for(int i=0;i<numberOfButton;i++)
        button[i]->update(window, currentState);
}

void menuState::render(sf::RenderWindow*& window)
{
    window->draw(menuBackgroundSprite);

    sf::RectangleShape rectangle;
    rectangle.setPosition(0, 0);
    rectangle.setSize(sf::Vector2f(120, window->getSize().y-40));
    rectangle.setFillColor(sf::Color(0,0,0,100));
    window->draw(rectangle);
    rectangle.setPosition(0, window->getSize().y-40);
    rectangle.setSize(sf::Vector2f(window->getSize().x, 40));
    rectangle.setFillColor(sf::Color(0,0,0,120));
    window->draw(rectangle);
    window->draw(logoImage);
    outtextxy(window, 10, 10, "Resolution", sf::Color(255,255,255,255), 30);
    int numberOfButton = button.size();
    for(int i=0;i<numberOfButton;i++)
        button[i]->render(window);

    if(state == storyState)
    {
        rectangle.setPosition(130, 50);
        rectangle.setSize(sf::Vector2f(window->getSize().x-140, window->getSize().y-100));
        rectangle.setFillColor(sf::Color(0,0,0,200));
        window->draw(rectangle);
        window->draw(story1Sprite);
    }
}
