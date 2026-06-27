#ifndef FIREBALL_H
#define FIREBALL_H

#include <SFML/Graphics.hpp>
#include "vector2d.h"
#include "animation.h"

class Fireball
{
public:
    Fireball(Animation *_anim, sf::Sprite _img, float xi, float yi, float xf, float yf, int _dist, int _dmg, int __px, float _angle):
    distance(_dist),
    angle(_angle),
    x(xi),
    y(yi),
    _px(__px),
    damage(_dmg),
    image(_img),
    anim(_anim)
    {
        move2d.setVector(sf::Vector2f(x, y), sf::Vector2f(xf, yf));
        lastUpdateTime = clock();
        image.setScale(_px/image.getLocalBounds().width, _px/image.getLocalBounds().height);
        image.setOrigin(_px/2., _px/2.);
        exist = true;
        anim->start();
    };

    void update()
    {
        float oldX, oldY;
        oldX = x;
        oldY = y;
        move2d.update(x, y, 7*_px, lastUpdateTime);
        image.setPosition(x, y);
        anim->setPosition(sf::Vector2f(x, y));
        anim->update();
        distance -= sqrt( pow(x - oldX, 2) + pow(y - oldY, 2) );
        if(distance < 0)
            exist = false;
    };

    void render(sf::RenderWindow *&window)
    {
        anim->render(window, angle);
        //window->draw(image);
    };

    Vector2d move2d;
    float distance;
    float angle;
    float x, y, _px;
    int damage;
    int lastUpdateTime;
    bool exist;
    sf::Sprite image;
    Animation *anim;
};
#endif // FIREBALL_H
