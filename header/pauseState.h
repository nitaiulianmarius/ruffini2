#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include<vector>
#include"stateMachine.h"
#include"button.h"

class pauseState:public stateMachine
{
public:
    pauseState(sf::RenderWindow *w, int _win, int _lose)
    {
        font.loadFromFile("data/font/madison.ttf");
        text.setFont(font);

        button.push_back(new bt::Button(10,w->getSize().y-125,200,30,font,"Resume",30));
        button.push_back(new bt::Button(10,w->getSize().y-95,200,30,font,"Save game",30));
        button.push_back(new bt::Button(10,w->getSize().y-65,200,30,font,"Return to main menu",30));
        button.push_back(new bt::Button(10,w->getSize().y-35,200,30,font,"Quit",30));

        win = _win;
        lose = _lose;
        saved = false;
        fullSlot = false;
    };
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

    std::vector<bt::Button*> button;
    sf::RenderWindow *window;
    int win, lose, saveTime, fullSlotTime;
    bool saved, fullSlot;

};

#endif // PAUSESTATE_H
