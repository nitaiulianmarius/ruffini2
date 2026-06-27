#include "animation.h"
#include <iostream>

Animation::Animation(sf::Sprite img, float w, float h, float rw, float rh, int uptime, int number, ...)
{
    width = w;
    height = h;
    realWidth = rw;
    realHeight = rh;
    defaultUpdateFrameTime = uptime;
    numberOfFrame = number;
    currentFrame = 0;

    va_list coordinate;
    va_start(coordinate, number);

    for(int i=1;i<=number;i++)
    {
        sf::Vector2f pos = va_arg(coordinate, sf::Vector2f);
        img.setTextureRect(sf::IntRect(pos.x, pos.y, w, h));
        img.setScale((float)w/rw, (float)h/rh);
        animation.push_back(img);
    }

    va_end(coordinate);

}

void Animation::add(sf::Sprite img, sf::Vector2f pos)
{
    img.setTextureRect(sf::IntRect(pos.x, pos.y, realWidth, realHeight));
    img.setScale((float)width/realWidth, (float)height/realHeight);
    animation.push_back(img);
    numberOfFrame++;
}

void Animation::render(sf::RenderWindow*& window, float angle)
{
    animation[currentFrame].setPosition(position);
    animation[currentFrame].setRotation(angle);

    window->draw(animation[currentFrame]);
}

void Animation::update()
{
    if(isRun)
    {
        if(clock() - lastUpdateFrameTime > defaultUpdateFrameTime)
        {
            if(currentFrame < numberOfFrame - 1)
                currentFrame++;
            else
                currentFrame = 0;

            lastUpdateFrameTime = clock();
        }
    }
}

void Animation::mirror(int origin)
{
    int numberOfAnimation = animation.size();
    for(int i=0;i<numberOfAnimation;i++)
        animation[i].setScale(-1,1), animation[i].setOrigin(origin,0);
}
