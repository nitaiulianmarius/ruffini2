#ifndef SHIELD_H
#define SHIELD_H

#include <SFML/Graphics.hpp>
#include "vector2d.h"

class Shield
{
public:
    Shield(float xi, float yi, int __px):
    x(xi),
    y(yi),
    _px(__px)
    {
        exist = true;
        r = 0.5*_px;
    };

    void update()
    {
        r += 0.08*_px;

        if(r > 3*_px)
            exist = false;
    };

    void render(sf::RenderWindow *&window)
    {
        sf::CircleShape circle(r);
        circle.setFillColor(sf::Color(0,0,0,230));
        circle.setOutlineColor(sf::Color(255,0,0,255));
        circle.setOutlineThickness(3);
        circle.setPosition(x, y);
        circle.setOrigin(r ,r);
        window->draw(circle);
    };

    float r;
    int lastUpdateTime;
    bool exist;
    float x, y, _px;
};
#endif // SHIELD_H
