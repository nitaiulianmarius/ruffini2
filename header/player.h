#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "time.h"
#include "vector2d.h"

class Player
{
public:
    Player(int _x, int _y, int _w, int _h, sf::Sprite _image, sf::RenderWindow *&_window):
    x(_x),
    y(_y),
    width(_w),
    height(_h),
    image(_image),
    window(_window)
    {
        _px = window->getSize().x / 20.;
        _py = window->getSize().y / 20.;
        image.setScale((float)width/image.getLocalBounds().width, (float)height/image.getLocalBounds().height);
        v = 1.5*_px;
        maxHeal = 100;
        heal = maxHeal;
        lovit1 = false;
        lovit2 = false;
        isInvi = false;
    };
    void update();
    void render();

    float x, y, _px, _py;
    float v;
    bool alive, isDestination;
    bool lovit1, lovit2;
    bool isInvi;
    float heal, maxHeal;
    int width;
    int height;
    int lovit1Time, lovit2Time;
    int defaultAttackTime;
    int lastUpdateTime;
    Vector2d move2d;
    sf::Sprite image;
    sf::RenderWindow *window;
    sf::Event event;
};

#endif // PLAYER_H
