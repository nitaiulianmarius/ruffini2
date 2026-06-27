#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <vector>
#include "stateMachine.h"
#include "menuState.h"

class Game
{
public:

    Game(int _width, int _height):
    width(_width),
    height(_height)
    {
        window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height),"Ruffini v2", sf::Style::Close);
        window->setFramerateLimit(60);
        myState.push_back(new menuState(window.get()));
    };

    ~Game()
    {
        for (stateMachine* state : myState)
            delete state;
    }

    bool isOpen() const { return window->isOpen(); };
    void handleEvent(){ myState[myState.size()-1]->handleEvent(window.get(), myState); };
    void update(){ myState[myState.size()-1]->update(window.get(), myState); };
    void render(){ auto* raw_window = window.get(); window->clear();myState[myState.size()-1]->render(raw_window);window->display(); };
    void outtextxy(sf::RenderWindow*& window, int x, int y, sf::String string, sf::Color color = { 0, 0, 0, 255 }, int size = 14)
    {
        text.setPosition(x, y);
        text.setString(string);
        text.setFillColor(color);
        text.setCharacterSize(size);
        window->draw(text);
    };

    int width, height;
    std::vector<stateMachine*> myState;
    std::unique_ptr<sf::RenderWindow> window;
    sf::Event event;
    sf::Font font;
    sf::Text text;
};

#endif // ENGINE_H
