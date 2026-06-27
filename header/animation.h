#ifndef ANIMATION_H
#define ANIMATION_H

#include<SFML/Graphics.hpp>
#include<vector>
#include<stdarg.h>
#include<time.h>

class Animation
{

public:
    Animation();
    Animation(sf::Sprite img, float w, float h, float rw, float rh, int uptime, int number=0, ...);

    void add(sf::Sprite img, sf::Vector2f pos);
    void render(sf::RenderWindow*& window, float angle = 0);
    void update();
    void reset(){ currentFrame = 0; };
    void setPosition(sf::Vector2f pos){ position = pos; };
    void start(){ lastUpdateFrameTime = clock(); isRun = true; };
    void stop(){ isRun = false; };
    void mirror(int origin);
    bool isRuning() { return isRun; };

    float width; // for render
    float height; // for render
    float realWidth; // from png
    float realHeight; // from png
    int numberOfFrame;
    int lastUpdateFrameTime;
    int defaultUpdateFrameTime;
    int currentFrame;
    bool isRun;

    sf::Vector2f position;
    std::vector<sf::Sprite> animation;

};


#endif // ANIMATION_H
