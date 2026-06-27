#include "enemy.h"
#include <iostream>

void Enemy::update()
{
    if(isDestination)
        move2d.update(x, y, v, lastUpdateTime);

    if(lovit1)
        move2d.update(x, y, 3*v, lastUpdateTime);

    if( abs(x - move2d.punctFinal.x) < 5 && abs(y - move2d.punctFinal.y < 5) )
        isDestination = false;

    if(y > window->getSize().y-80-2*_py || sqrt( pow(x-9*_px, 2) + pow(y-6*_py-40, 2)) > 10*_py-50)
        isDestination = false;

    if(isDestination == false && lovit1 == false && lovit2 == false)
    {
        int tempx, tempy;
        tempx = rand()%(10*(int)_px) + 5*_px;
        tempy = rand()%(16*(int)_py-80);
        move2d.setVector(sf::Vector2f(x, y), sf::Vector2f(tempx, tempy));
        isDestination = true;
    }

    if(x < 0 || x > window->getSize().x - 2*_px ||
       y < 0 || y > window->getSize().y - 4*_py - 80)
        lovit1 = false, lovit2 = false;

    if( sqrt( pow(x-9*_px, 2) + pow(y-6*_py-40, 2)) > 10*_py-50)
        heal -= 0.1;

    if(heal < 0)
        heal = 0;
}

void Enemy::render()
{
    image.setPosition(x, y);
    window->draw(image);
    float p = (float)heal/maxHeal*2.*_py;
    sf::RectangleShape line(sf::Vector2f(p, 3));
    line.setPosition(x, y);
    window->draw(line);
}
