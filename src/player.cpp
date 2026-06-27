#include "player.h"

void Player::update()
{
    if(isDestination)
        move2d.update(x, y, v, lastUpdateTime);

    if(lovit1)
        move2d.update(x, y, 3*v, lastUpdateTime);

    if( abs(x - move2d.punctFinal.x) < 2 && abs(y - move2d.punctFinal.y < 2) )
        isDestination = false;

    if(x < 0 || x > window->getSize().x - 2*_px ||
       y < 0 || y > window->getSize().y - 4*_py - 80)
        lovit1 = false, lovit2 = false;

    if( sqrt( pow(x-9*_px, 2) + pow(y-6*_py-40, 2)) > 10*_py-50)
        heal -= 0.1;

    if(heal < 0)
        heal = 0;
}

void Player::render()
{
    image.setPosition(x, y);
    window->draw(image);
    float p = (float)heal/maxHeal*2.*_py;
    sf::RectangleShape line(sf::Vector2f(p, 3));
    line.setPosition(x, y);
    window->draw(line);
}
