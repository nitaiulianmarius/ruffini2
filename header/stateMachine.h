#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

class stateMachine
{
public:
    stateMachine(){};
    virtual ~stateMachine() = default;

    virtual void handleEvent(sf::RenderWindow*,std::vector<stateMachine*>&) = 0;
    virtual void update(sf::RenderWindow*,std::vector<stateMachine*>&) = 0;
    virtual void render(sf::RenderWindow*&) = 0;

    bool sound;
    float _px, _py;

    sf::RenderWindow *window;
    sf::Event event;
    sf::Texture logoTexture;
    sf::Sprite logoImage;
    sf::Texture buttonBackgroundTexture, menuBackgroundTexture;
    sf::Sprite buttonBackgroundSprite, menuBackgroundSprite;
    sf::Music backgroundMusic, fireballMusic, iceballMusic, shieldMusic, teleportMusic;

    sf::Font font;
    sf::Text text;

};
#endif // STATEMACHINE_H
