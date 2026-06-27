#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <iostream>
#include "stateMachine.h"
#include "animation.h"
#include "fireball.h"
#include "iceball.h"
#include "shield.h"
#include "button.h"
#include "player.h"
#include "enemy.h"

#define playerState 1
#define enemyState 2
#define fireballState 3
#define iceballState 4
#define shieldState 5
#define teleportState 6


class playState:public stateMachine
{
public:
    playState(sf::RenderWindow *window)
    {
        _px = window->getSize().x / 20.;
        _py = window->getSize().y / 20.;

        font.loadFromFile("data/font/madison.ttf");
        backgroundTexture.loadFromFile("data/image/background.png");
        islandTexture.loadFromFile("data/image/island.png");
        playerTexture.loadFromFile("data/image/player.png");
        enemyTexture.loadFromFile("data/image/enemy.png");
        playerCTexture.loadFromFile("data/image/playerc.png");
        enemyCTexture.loadFromFile("data/image/enemyc.png");
        fireballBTexture.loadFromFile("data/image/fireballb.png");
        iceballBTexture.loadFromFile("data/image/iceballb.png");
        shieldBTexture.loadFromFile("data/image/shieldb.png");
        teleportBTexture.loadFromFile("data/image/teleportb.png");
        fireballTexture.loadFromFile("data/image/fireball.png");
        iceballTexture.loadFromFile("data/image/iceball.png");
        heartTexture.loadFromFile("data/image/heart.png");
        iceblockTexture.loadFromFile("data/image/iceblock.png");
        soundonTexture.loadFromFile("data/image/soundon.png");
        soundoffTexture.loadFromFile("data/image/soundoff.png");
        invisibilityBTexture.loadFromFile("data/image/invisibility.png");
        invisibilitySTexture.loadFromFile("data/image/invisibilityplayer.png");
        text.setFont(font);
        backgroundSprite.setTexture(backgroundTexture);
        islandSprite.setTexture(islandTexture);
        playerSprite.setTexture(playerTexture);
        enemySprite.setTexture(enemyTexture);
        playerCSprite.setTexture(playerCTexture);
        enemyCSprite.setTexture(enemyCTexture);
        fireballBSprite.setTexture(fireballBTexture);
        iceballBSprite.setTexture(iceballBTexture);
        shieldBSprite.setTexture(shieldBTexture);
        teleportBSprite.setTexture(teleportBTexture);
        fireballSprite.setTexture(fireballTexture);
        iceballSprite.setTexture(iceballTexture);
        heartSprite.setTexture(heartTexture);
        iceblockSprite.setTexture(iceblockTexture);
        soundonSprite.setTexture(soundonTexture);
        soundoffSprite.setTexture(soundoffTexture);
        invisibilityBSprite.setTexture(invisibilityBTexture);
        invisibilitySSprite.setTexture(invisibilitySTexture);

        backgroundSprite.setScale((float)window->getSize().x/backgroundSprite.getLocalBounds().width, (float)(window->getSize().y-60)/backgroundSprite.getLocalBounds().height);
        islandSprite.setScale((float)(window->getSize().y-80)/islandSprite.getLocalBounds().width, (float)(window->getSize().y-80)/islandSprite.getLocalBounds().height);
        islandSprite.setPosition(10*_px-islandSprite.getGlobalBounds().width/2, 10);
        playerCSprite.setPosition(5, window->getSize().y-55);
        playerCSprite.setScale(50./playerCSprite.getLocalBounds().width, 50./playerCSprite.getLocalBounds().height);
        enemyCSprite.setPosition(5, window->getSize().y-55);
        enemyCSprite.setScale(50./enemyCSprite.getLocalBounds().width, 50./enemyCSprite.getLocalBounds().height);
        fireballBSprite.setPosition(window->getSize().x/2-80, window->getSize().y-45);
        fireballBSprite.setScale(35./fireballBSprite.getLocalBounds().width, 35./fireballBSprite.getLocalBounds().height);
        iceballBSprite.setPosition(window->getSize().x/2-40, window->getSize().y-45);
        iceballBSprite.setScale(35./iceballBSprite.getLocalBounds().width, 35./iceballBSprite.getLocalBounds().height);
        shieldBSprite.setPosition(window->getSize().x/2, window->getSize().y-45);
        shieldBSprite.setScale(35./shieldBSprite.getLocalBounds().width, 35./shieldBSprite.getLocalBounds().height);
        teleportBSprite.setPosition(window->getSize().x/2+40, window->getSize().y-45);
        teleportBSprite.setScale(35./teleportBSprite.getLocalBounds().width, 35./teleportBSprite.getLocalBounds().height);
        invisibilityBSprite.setPosition(window->getSize().x/2+80, window->getSize().y-45);
        invisibilityBSprite.setScale(35./invisibilityBSprite.getLocalBounds().width, 35./invisibilityBSprite.getLocalBounds().height);
        invisibilitySSprite.setScale(_px/invisibilitySSprite.getLocalBounds().width, _py/invisibilitySSprite.getLocalBounds().height);
        iceblockSprite.setScale(2.1*_px/iceblockSprite.getLocalBounds().width, 4.1*_py/iceblockSprite.getLocalBounds().height);
        soundonSprite.setScale(35./soundonSprite.getLocalBounds().width, 35./soundonSprite.getLocalBounds().height);
        soundoffSprite.setScale(35./soundoffSprite.getLocalBounds().width, 35./soundoffSprite.getLocalBounds().height);
        soundonSprite.setPosition(window->getSize().x - 40, 5);
        soundoffSprite.setPosition(window->getSize().x - 40, 5);

        fireballAnimation = new Animation(fireballSprite, 40, 40, 40, 70, 80);
        for(int i=0; i<7; i++)
            fireballAnimation->add(fireballSprite, sf::Vector2f(i*40, 0));
        for(int i=0; i<7; i++)
            fireballAnimation->add(fireballSprite, sf::Vector2f(i*40, 72));


        iceballAnimation = new Animation(iceballSprite, 35, 35, 192, 110, 90);
        for(int i=0; i<3; i++)
            iceballAnimation->add(iceballSprite, sf::Vector2f(i*192, 0));

        heartAnimation = new Animation(heartSprite, 40, 40, 480, 455, 100);
        heartAnimation->add(heartSprite, sf::Vector2f(0, 0));
        heartAnimation->add(heartSprite, sf::Vector2f(480, 0));
        heartAnimation->setPosition(sf::Vector2f(20*_px-100, 20*_py-55));
        heartAnimation->start();

        player = new Player(6*_px, 7*_py, 2*_px, 4*_py, playerSprite, window);
        enemy = new Enemy(13*_px, 7*_py, 2*_px, 4*_py, enemySprite, window);
        fireballTime = fireballTimeCPU = -10000;
        iceballTime = iceballTimeCPU = -10000;
        shieldTime = shieldTimeCPU = -10000;
        teleportTime = teleportTimeCPU = -10000;
        invisibilityTime = invisibilityTimeCPU = -10000;
        state = playerState;
        winScore = 0;
        loseScore = 0;
        sound = true;
        soundSprite = soundonSprite;

        backgroundMusic.openFromFile("data/music/background.ogg");
        fireballMusic.openFromFile("data/music/fireball.ogg");
        iceballMusic.openFromFile("data/music/iceball.ogg");
        shieldMusic.openFromFile("data/music/shield.ogg");
        teleportMusic.openFromFile("data/music/teleport.ogg");
        backgroundMusic.play();
        backgroundMusic.setLoop(true);
        backgroundMusic.setVolume(100);
        shieldMusic.setVolume(60);
    };

    void freeMemory();
    void handleEvent(sf::RenderWindow*,std::vector<stateMachine*>&);
    void update(sf::RenderWindow*,std::vector<stateMachine*>&);
    void render(sf::RenderWindow*&);
    void playerInfo(sf::RenderWindow*&);
    void enemyInfo(sf::RenderWindow*&);
    void IACPU();
    void collision();
    void init();

    void outtextxy(sf::RenderWindow*& window, int x, int y, sf::String string, sf::Color color = { 0, 0, 0, 255 }, int size = 14)
    {
        text.setPosition(x, y);
        text.setString(string);
        text.setFillColor(color);
        text.setCharacterSize(size);
        window->draw(text);
    };

    int state;
    int winScore, loseScore;
    int xMouse, yMouse, width, height;
    int fireballTime, iceballTime, shieldTime, teleportTime, invisibilityTime;
    int fireballTimeCPU, iceballTimeCPU, shieldTimeCPU, teleportTimeCPU, invisibilityTimeCPU;
    bool sound;
    Player *player;
    Enemy *enemy;
    Animation *fireballAnimation, *iceballAnimation, *heartAnimation;
    std::vector<Fireball*> fireball, fireballCPU;
    std::vector<Iceball*> iceball, iceballCPU;
    std::vector<Shield*> shield, shieldCPU;
    std::vector<bt::Button*> button;
    sf::Texture backgroundTexture, islandTexture, playerTexture, enemyTexture, playerCTexture, enemyCTexture;
    sf::Texture fireballBTexture, iceballBTexture, shieldBTexture, teleportBTexture;
    sf::Texture fireballTexture, iceballTexture, heartTexture, iceblockTexture, soundonTexture, soundoffTexture;
    sf::Texture invisibilityBTexture, invisibilitySTexture;
    sf::Sprite backgroundSprite, islandSprite, playerSprite, enemySprite, playerCSprite, enemyCSprite;
    sf::Sprite fireballBSprite, iceballBSprite, shieldBSprite, teleportBSprite;
    sf::Sprite fireballSprite, iceballSprite, heartSprite, iceblockSprite, soundonSprite, soundoffSprite;
    sf::Sprite invisibilityBSprite, invisibilitySSprite;
    sf::Sprite soundSprite;

};

#endif // PLAYSTATE_H
