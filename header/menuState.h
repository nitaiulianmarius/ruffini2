#ifndef MENUSTATE_H
#define MENUSTATE_H

#include"stateMachine.h"
#include"button.h"

#define noneState 0
#define storyState 1

class menuState:public stateMachine
{
public:
    menuState(sf::RenderWindow *w)
    {
        window = w;
        _px = window->getSize().x / 20.;
        _py = window->getSize().y / 20.;
        font.loadFromFile("data/font/madison.ttf");
        menuBackgroundTexture.loadFromFile("data/image/menubackground.png");
        story1Texture.loadFromFile("data/story/story1.png");
        logoTexture.loadFromFile("data/image/logo.png");
        text.setFont(font);
        menuBackgroundSprite.setTexture(menuBackgroundTexture);
        story1Sprite.setTexture(story1Texture);
        logoImage.setTexture(logoTexture);

        story1Sprite.setPosition(130, 50);
        logoImage.setPosition(window->getSize().x/2-54, 0);
        menuBackgroundSprite.setScale((float)window->getSize().x/menuBackgroundSprite.getLocalBounds().width, (float)window->getSize().y/menuBackgroundSprite.getLocalBounds().height);
        story1Sprite.setScale((float)(window->getSize().x-140)/story1Sprite.getLocalBounds().width, (float)(window->getSize().y-100)/story1Sprite.getLocalBounds().height);

        button.push_back(new bt::Button(130,window->getSize().y-40,150,30,font,"Start game",30));
        button.push_back(new bt::Button(280,window->getSize().y-40,150,30,font,"Load game",30));
        button.push_back(new bt::Button(430,window->getSize().y-40,100,30,font,"Story",30));
        button.push_back(new bt::Button(window->getSize().x-60,window->getSize().y-40,50,30,font,"Quit",30));

        button.push_back(new bt::Button(10,50,100,30,font,"600x400",25));
        button.push_back(new bt::Button(10,80,100,30,font,"720x640",25));
        button.push_back(new bt::Button(10,110,100,30,font,"800x600",25));
        button.push_back(new bt::Button(10,140,100,30,font,"1080x720",25));
        button.push_back(new bt::Button(10,170,100,30,font,"1280x720",25));
        button.push_back(new bt::Button(10,200,100,30,font,"1360x768",25));

        state = noneState;
    }

    void freeMemory();
    void handleEvent(sf::RenderWindow*,std::vector<stateMachine*>&);
    void update(sf::RenderWindow*,std::vector<stateMachine*>&);
    void render(sf::RenderWindow*&);

    void outtextxy(sf::RenderWindow*& window, int x, int y, sf::String string, sf::Color color = { 0, 0, 0, 255 }, int size = 14)
    {
        text.setPosition(x, y);
        text.setString(string);
        text.setFillColor(color);
        text.setCharacterSize(size);
        window->draw(text);
    };

    int state;
    std::vector<bt::Button*> button;
    sf::Texture story1Texture;
    sf::Sprite story1Sprite;
};

#endif // MENUSTATE_H
