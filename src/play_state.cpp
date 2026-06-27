#include<fstream>
#include"playState.h"
#include"pauseState.h"
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>

void playState::freeMemory()
{
    int numberOfButton = button.size();
    for(int i=numberOfButton-1;i>=0;i--)
    {
        delete button[i];
        button.pop_back();
    }
}

void playState::handleEvent(sf::RenderWindow* window,std::vector<stateMachine*>& currentState)
{
    xMouse = sf::Mouse::getPosition(*window).x;
    yMouse = sf::Mouse::getPosition(*window).y;
    width = window->getSize().x;
    height = window->getSize().y;

    while(window->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            window->close();

        if(event.type == sf::Event::LostFocus)
            currentState.push_back(new pauseState(window, winScore, loseScore));

        if(state == playerState)
        {
            // Move the player toward the selected destination.
            if(player->lovit1 == false && player->lovit2 == false)
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
            {
                player->move2d.setVector(sf::Vector2f(player->x, player->y),
                                         sf::Vector2f(xMouse-player->width/2, std::min<float>(height - 4*_py - 60, yMouse-player->height/2)));
                player->isDestination = true;
                player->lastUpdateTime = clock();
            }

            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                if(height-45 <= yMouse && yMouse <= height-10)
                {
                    if(width/2-80 <= xMouse && xMouse <= width/2-45 && clock() - fireballTime > 3000)
                        state = fireballState;

                    if(width/2-40 <= xMouse && xMouse <= width/2-5 && clock() - iceballTime > 4000)
                        state = iceballState;

                    if(width/2 <= xMouse && xMouse <= width/2+35 && clock() - shieldTime > 4000)
                    {
                        shield.push_back(new Shield(player->x+_px, player->y+1.5*_px, _px));
                        shieldTime = clock();
                        if(sound)
                            shieldMusic.play();
                    }

                    if(width/2+40 <= xMouse && xMouse <= width/2+75 && clock() - teleportTime > 2500)
                        state = teleportState;

                    if(width/2+80 <= xMouse && xMouse <= width/2+115 && clock() - invisibilityTime > 10000)
                        player->isInvi = true, invisibilityTime = clock();

                }

                    if(enemy->x <= xMouse && xMouse <= enemy->x + enemy->width &&
                       enemy->y <= yMouse && yMouse <= enemy->y + enemy->height &&
                        state == playerState)
                        state = enemyState;

            }
        }

        if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
        {
            if(state == fireballState ||
                state == iceballState ||
                state == shieldState ||
                state == teleportState)
                state = playerState;
        }

        if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            if(player->x <= xMouse && xMouse <= player->x + player->width &&
               player->y <= yMouse && yMouse <= player->y + player->height &&
               state == enemyState)
                state = playerState;

            if(state == fireballState)
                if(yMouse < height-60)
                {
                    int dist;
                    dist = static_cast<int>(std::min<float>(sqrt( pow(xMouse - player->x, 2) + pow(yMouse - player->y, 2) ), 5*_px));
                    fireball.push_back(new Fireball(fireballAnimation, fireballBSprite, player->x+_px, player->y+_py, xMouse, yMouse, dist, 15, _px, atan2(yMouse-player->y+_py, xMouse-player->x+_px)*180/3.14-90));
                    state = playerState;
                    fireballTime = clock();
                    if(sound)
                        fireballMusic.play();
                }

            if(state == iceballState)
                if(yMouse < height-60)
                {
                    int dist;
                    dist = static_cast<int>(std::min<float>(sqrt( pow(xMouse - player->x, 2) + pow(yMouse - player->y, 2) ), 5*_px));
                    iceball.push_back(new Iceball(iceballAnimation, iceballBSprite, player->x+_px, player->y+_py, xMouse, yMouse, dist, 10, _px));
                    state = playerState;
                    iceballTime = clock();
                    if(sound)
                        iceballMusic.play();
                }

            if(state == teleportState)
                if(yMouse < height-60-2*_py)
                {
                    float l, dist = 2.5*_px;
                    l = sqrt( pow(xMouse-player->x, 2) + pow(yMouse-player->y, 2) );
                    if(l < dist)
                    {
                        player->x = xMouse - _px;
                        player->y = yMouse - 2*_py;
                    }
                    else
                    {
                        Vector2d mov;
                        float vx, vy;
                        mov.setVector( sf::Vector2f(player->x, player->y), sf::Vector2f(xMouse-_px, yMouse-2*_py) );
                        while(dist>0)
                        {
                            float oldX = player->x, oldY = player->y;
                            vx = mov.vectorNormalizat.x;
                            vy = mov.vectorNormalizat.y;
                            player->x += vx;
                            player->y += vy;
                            dist -= sqrt( pow(player->x-oldX, 2) + pow(player->y-oldY, 2) );
                        }
                    }


                    player->isDestination = false;
                    state = playerState;
                    teleportTime = clock();
                    if(sound)
                        teleportMusic.play();
                }

            // sound
            if(20*_px - 40 < xMouse && xMouse < 20*_px-5 &&
               5 < yMouse && yMouse < 40)
            {
                if(sound)
                {
                    sound = false;
                    soundSprite = soundoffSprite;
                    backgroundMusic.pause();
                }
                else
                {
                    sound = true;
                    soundSprite = soundonSprite;
                    backgroundMusic.play();
                }
            }
        }

        if(event.type == sf::Event::KeyPressed)
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                if(state == playerState || state == enemyState)
                    currentState.push_back(new pauseState(window, winScore, loseScore));

                if(state == fireballState ||
                    state == iceballState ||
                    state == shieldState ||
                    state == teleportState)
                    state = playerState;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
                state = playerState;

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
                state = enemyState;

            if(state == playerState)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && clock() - fireballTime > 3000)
                    state = fireballState;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && clock() - iceballTime > 4000)
                    state = iceballState;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::E) && clock() - shieldTime > 4000)
                {
                    shield.push_back(new Shield(player->x+_px, player->y+1.5*_px, _px));
                    shieldTime = clock();
                    if(sound)
                        shieldMusic.play();
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::R) && clock() - teleportTime > 2500)
                    state = teleportState;

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::T) && clock() - invisibilityTime > 10000 && winScore>=10)
                    player->isInvi = true, invisibilityTime = clock();

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                    player->isDestination = false;
            }
        }
    } /// while(event)
}

void playState::update(sf::RenderWindow* window,std::vector<stateMachine*>& currentState)
{
    (void)window;
    (void)currentState;
    player->update();
    enemy->update();
    IACPU();
    collision();

    if(player->heal == 0)
    {
        loseScore++;
        init();
    }

    if(enemy->heal == 0)
    {
        winScore++;
        init();
    }

    if(player->isInvi)
        if(clock()-invisibilityTime > 3000)
            player->isInvi = false;
    if(enemy->isInvi)
        if(clock()-invisibilityTimeCPU > 3000)
            enemy->isInvi = false;

    for(std::size_t i=0; i<fireball.size(); i++)
        if(fireball[i]->exist)
           fireball[i]->update();

    for(std::size_t i=0; i<iceball.size(); i++)
        if(iceball[i]->exist)
           iceball[i]->update();

    for(std::size_t i=0; i<shield.size(); i++)
        if(shield[i]->exist)
           shield[i]->update();

    for(std::size_t i=0; i<fireballCPU.size(); i++)
        if(fireballCPU[i]->exist)
           fireballCPU[i]->update();

    for(std::size_t i=0; i<iceballCPU.size(); i++)
        if(iceballCPU[i]->exist)
           iceballCPU[i]->update();

    for(std::size_t i=0; i<shieldCPU.size(); i++)
        if(shieldCPU[i]->exist)
           shieldCPU[i]->update();
}

void playState::render(sf::RenderWindow*& window)
{

    window->draw(backgroundSprite);
    window->draw(islandSprite);
    player->render();
    if(player->lovit2)
    {
        iceblockSprite.setPosition(player->x, player->y);
        window->draw(iceblockSprite);
    }
    if(player->isInvi)
    {
        invisibilitySSprite.setPosition(player->x+_px/2, player->y-_py);
        window->draw(invisibilitySSprite);
    }
    if(enemy->isInvi == false)
        enemy->render();
    if(enemy->lovit2)
    {
        iceblockSprite.setPosition(enemy->x, enemy->y);
        window->draw(iceblockSprite);
    }

    if(height-45 < yMouse && yMouse < height-10)
    {
        if(width/2-80 < xMouse && xMouse < width/2-45)
        {
            outtextxy(window, xMouse-100, yMouse-50, "Fireball (Q) - launches a fire burst", sf::Color(255,255,255,255),20);
        }
        else if(width/2-40 < xMouse && xMouse < width/2-5)
        {
            outtextxy(window, xMouse-100, yMouse-50, "Iceball (W) - freezes the player", sf::Color(255,255,255,255),20);
        }
        else if(width/2 < xMouse && xMouse < width/2+35)
        {
            outtextxy(window, xMouse-150, yMouse-50, "Shield (E) - creates a protection field", sf::Color(255,255,255,255),20);
        }
        else if(width/2+40 < xMouse && xMouse < width/2+75)
        {
            outtextxy(window, xMouse-140, yMouse-50, "Teleport (R) - moves the player", sf::Color(255,255,255,255),20);
        }
        else if(width/2+80 < xMouse && xMouse < width/2+115)
        {
            outtextxy(window, xMouse-160, yMouse-50,"Invisibility (T) - hides the player", sf::Color(255,255,255,255),20);
            if(winScore < 10)
                outtextxy(window, xMouse-160, yMouse-40,"Requires 10 wins", sf::Color(255,0,0,255),20);
        }
    }

    for(std::size_t i=0; i<fireball.size(); i++)
        if(fireball[i]->exist)
            fireball[i]->render(window);

    for(std::size_t i=0; i<iceball.size(); i++)
        if(iceball[i]->exist)
            iceball[i]->render(window);

    for(std::size_t i=0; i<shield.size(); i++)
        if(shield[i]->exist)
            shield[i]->render(window);

    for(std::size_t i=0; i<fireballCPU.size(); i++)
        if(fireballCPU[i]->exist)
            fireballCPU[i]->render(window);

    for(std::size_t i=0; i<iceballCPU.size(); i++)
        if(iceballCPU[i]->exist)
            iceballCPU[i]->render(window);

    for(std::size_t i=0; i<shieldCPU.size(); i++)
        if(shieldCPU[i]->exist)
            shieldCPU[i]->render(window);

    if(state != enemyState)
    {
        playerInfo(window);
        window->draw(fireballBSprite);
        window->draw(iceballBSprite);
        window->draw(shieldBSprite);
        window->draw(teleportBSprite);
        window->draw(invisibilityBSprite);

        sf::RectangleShape rec;
        rec.setFillColor(sf::Color(0,0,0,150));
        rec.setPosition(width/2-80, height-45);
        rec.setSize(sf::Vector2f(35, std::max<float>(0,35-35*(clock()-fireballTime)/3000.)));
        window->draw(rec);

        rec.setPosition(width/2-40, height-45);
        rec.setSize(sf::Vector2f(35, std::max<float>(0,35-35*(clock()-iceballTime)/4000.)));
        window->draw(rec);

        rec.setPosition(width/2, height-45);
        rec.setSize(sf::Vector2f(35, std::max<float>(0,35-35*(clock()-shieldTime)/4000.)));
        window->draw(rec);

        rec.setPosition(width/2+40, height-45);
        rec.setSize(sf::Vector2f(35, std::max<float>(0,35-35*(clock()-teleportTime)/2500.)));
        window->draw(rec);

        rec.setPosition(width/2+80, height-45);
        rec.setSize(sf::Vector2f(35, std::max<float>(0,35-35*(clock()-invisibilityTime)/10000.)));
        window->draw(rec);

        if(state == iceballState || state == fireballState || state == teleportState)
        {
            sf::CircleShape circle(_px/4);
            circle.setPosition(xMouse-_px/4, yMouse-_px/4);
            circle.setFillColor(sf::Color(255,0,0,100));
            window->draw(circle);
        }
    }

    if(state == enemyState)
        enemyInfo(window);

    window->draw(soundSprite);
}

void playState::playerInfo(sf::RenderWindow*& window)
{
    window->draw(playerCSprite);
    char ws[25], ls[25], hl[25];
    sprintf(ws, "win: %d", winScore);
    sprintf(ls, "lose: %d", loseScore);
    sprintf(hl, "%.0f/%.0f", player->heal, player->maxHeal);
    sf::String winSir = ws;
    sf::String loseSir = ls;
    sf::String hlSir = hl;

    outtextxy(window, 65, height-50, winSir, sf::Color(255,255,255,255), 25);
    outtextxy(window, 65, height-30, loseSir, sf::Color(255,255,255,255), 25);
    outtextxy(window, 20*_px-100, 20*_py-30, hlSir, sf::Color(255,255,255,255), 25);

    heartAnimation->update();
    heartAnimation->defaultUpdateFrameTime =  100*player->maxHeal/player->heal;
    heartAnimation->render(window);
}

void playState::enemyInfo(sf::RenderWindow*& window)
{
    window->draw(enemyCSprite);
    char ws[25], ls[25], hl[25];
    sprintf(ws, "win: %d", loseScore);
    sprintf(ls, "lose: %d", winScore);
    sprintf(hl, "%.0f/%.0f", enemy->heal, enemy->maxHeal);
    sf::String winSir = ws;
    sf::String loseSir = ls;
    sf::String hlSir = hl;

    outtextxy(window, 65, height-50, winSir, sf::Color(255,255,255,255), 25);
    outtextxy(window, 65, height-30, loseSir, sf::Color(255,255,255,255), 25);
    outtextxy(window, 20*_px-100, 20*_py-30, hlSir, sf::Color(255,255,255,255), 25);

    heartAnimation->update();
    heartAnimation->defaultUpdateFrameTime =  100*enemy->maxHeal/enemy->heal;
    heartAnimation->render(window);
}

void playState::IACPU()
{
    int dist, playerDist;
    playerDist = sqrt( pow(enemy->x - player->x, 2) + pow(enemy->y - player->y, 2) );
    dist = static_cast<int>(std::min<float>(playerDist, 5*_px));
if(player->isInvi == false)
{
    // iceball
    if(playerDist < 2.5*_px && clock() - iceballTimeCPU > 4000)
    {
        iceballCPU.push_back(new Iceball(iceballAnimation, iceballBSprite, enemy->x+_px, enemy->y+_py, player->x+_px, player->y+_py, dist, 10, _px));
        iceballTimeCPU = clock();
        if(sound)
            iceballMusic.play();
    }

    // fireball
    if(playerDist < 5*_px && clock() - fireballTimeCPU > 3000)
    {
        fireballCPU.push_back(new Fireball(fireballAnimation, fireballBSprite, enemy->x+_px, enemy->y+_py, player->x+_px, player->y+_py, dist, 15, _px, atan2(enemy->y-player->y, enemy->x-player->x)*180/3.14+90));
        fireballTimeCPU = clock();
        if(sound)
            fireballMusic.play();
    }

    if(clock() - shieldTimeCPU > 4000)
    {
        for(std::size_t i=0; i<fireball.size(); i++)
        if(fireball[i]->exist)
        {
            int dx, dy;
            dx = enemy->x - fireball[i]->x;
            dy = enemy->y - fireball[i]->y;
            if(abs(dx) < 2*_px && abs(dy) < 2*_py)
            {
                shieldCPU.push_back(new Shield(enemy->x+_px, enemy->y+1.5*_px, _px));
                shieldTimeCPU = clock();
                if(sound)
                    shieldMusic.play();
            }
        }

        for(std::size_t i=0; i<iceball.size(); i++)
        if(iceball[i]->exist)
        {
            int dx, dy;
            dx = enemy->x - iceball[i]->x;
            dy = enemy->y - iceball[i]->y;
            if(abs(dx) < 2*_px && abs(dy) < 2*_py)
            {
                shieldCPU.push_back(new Shield(enemy->x+_px, enemy->y+1.5*_px, _px));
                shieldTimeCPU = clock();
                if(sound)
                    shieldMusic.play();
            }
        }
    }
}
    if(clock() - teleportTimeCPU > 2500)
        if(enemy->x < 5*_px || enemy->x > 15*_px)
        {
            Vector2d mov;
            float vx, vy;
            mov.setVector( sf::Vector2f(enemy->x, enemy->y), sf::Vector2f(10*_px, 8*_py) );
            while(dist>0)
            {
                float oldX = enemy->x, oldY = enemy->y;
                vx = mov.vectorNormalizat.x;
                vy = mov.vectorNormalizat.y;
                enemy->x += vx;
                enemy->y += vy;
                dist -= sqrt( pow(enemy->x-oldX, 2) + pow(enemy->y-oldY, 2) );
            }
            teleportTimeCPU = clock();
            enemy->isDestination = false;
            if(sound)
                teleportMusic.play();
        }

    if(clock() - invisibilityTimeCPU > 10000 && loseScore>=10)
    {
        enemy->isInvi = true;
        invisibilityTimeCPU = clock();
    }



}

void playState::collision()
{

    for(std::size_t i=0; i<fireballCPU.size(); i++)
    {
        if(fireballCPU[i]->exist &&
           player->x < fireballCPU[i]->x && fireballCPU[i]->x < player->x + 2*_px &&
           player->y < fireballCPU[i]->y && fireballCPU[i]->y < player->y + 4*_py )
        {
            player->heal -= fireballCPU[i]->damage;
            player->lovit1 = true;
            player->isDestination = false;
            fireballCPU[i]->exist = false;
            player->lovit1Time = clock();
            player->lastUpdateTime = clock();
            player->move2d = fireballCPU[i]->move2d;
        }
        else
            for(std::size_t j=0; j<shield.size(); j++)
                if(shield[j]->exist &&
                   sqrt( pow(shield[j]->x-fireballCPU[i]->x,2) + pow(shield[j]->y-fireballCPU[i]->y,2) ) < shield[j]->r)
                    {
                        fireballCPU[i]->exist = false;
                    }
    }
    for(std::size_t i=0; i<iceballCPU.size(); i++)
    {
        if(iceballCPU[i]->exist &&
           player->x < iceballCPU[i]->x && iceballCPU[i]->x < player->x + 2*_px &&
           player->y < iceballCPU[i]->y && iceballCPU[i]->y < player->y + 4*_py )
        {
            player->lovit2 = true;
            player->isDestination = false;
            iceballCPU[i]->exist = false;
            player->lovit2Time = clock();
        }
    }

    if(player->lovit1)
    {
        if(clock() - player->lovit1Time > 600)
            player->lovit1 = false;
        else
            player->isDestination = false;
    }
    if(player->lovit2)
    {
        if(clock() - player->lovit2Time > 750)
            player->lovit2 = false;
        else
            player->isDestination = false;
    }





    for(std::size_t i=0; i<fireball.size(); i++)
    {
        if(fireball[i]->exist &&
           enemy->x < fireball[i]->x && fireball[i]->x < enemy->x + 2*_px &&
           enemy->y < fireball[i]->y && fireball[i]->y < enemy->y + 4*_py )
        {
            enemy->heal -= fireball[i]->damage;
            enemy->lovit1 = true;
            enemy->isDestination = false;
            fireball[i]->exist = false;
            enemy->lovit1Time = clock();
            enemy->lastUpdateTime = clock();
            enemy->move2d = fireball[i]->move2d;
        }
        else
            for(std::size_t j=0; j<shieldCPU.size(); j++)
                if(shieldCPU[j]->exist &&
                   sqrt( pow(shieldCPU[j]->x-fireball[i]->x,2) + pow(shieldCPU[j]->y-fireball[i]->y,2) ) < shieldCPU[j]->r)
                    {
                        fireball[i]->exist = false;
                    }
    }
    for(std::size_t i=0; i<iceball.size(); i++)
    {
        if(iceball[i]->exist &&
           enemy->x < iceball[i]->x && iceball[i]->x < enemy->x + 2*_px &&
           enemy->y < iceball[i]->y && iceball[i]->y < enemy->y + 4*_py )
        {
            enemy->lovit2 = true;
            enemy->isDestination = false;
            iceball[i]->exist = false;
            enemy->lovit2Time = clock();
        }
    }

    if(enemy->lovit1)
    {
        if(clock() - enemy->lovit1Time > 600)
            enemy->lovit1 = false;
        else
            enemy->isDestination = false;
    }
    if(enemy->lovit2)
    {
        if(clock() - enemy->lovit2Time > 750)
            enemy->lovit2 = false, enemy->lastUpdateTime = clock();
        else
            enemy->isDestination = false;
    }
}

void playState::init()
{

    player->x = 6*_px;
    player->y = 7*_py;
    player->heal = 100;
    player->lovit1 = player->lovit2 = false;
    player->isInvi = false;
    for(int i=static_cast<int>(fireball.size())-1; i>=0; i--)
        delete fireball[i];
    for(int i=static_cast<int>(iceball.size())-1; i>=0; i--)
        delete iceball[i];
    for(int i=static_cast<int>(shield.size())-1; i>=0; i--)
        delete shield[i];
    fireball.clear();
    iceball.clear();
    shield.clear();

    enemy->x = 13*_px;
    enemy->y = 7*_py;
    enemy->heal = 100;
    enemy->lovit1 = enemy->lovit2 = false;
    enemy->isInvi = false;
    for(int i=static_cast<int>(fireballCPU.size())-1; i>=0; i--)
        delete fireballCPU[i];
    for(int i=static_cast<int>(iceballCPU.size())-1; i>=0; i--)
        delete iceballCPU[i];
    for(int i=static_cast<int>(shieldCPU.size())-1; i>=0; i--)
        delete shieldCPU[i];
    fireballCPU.clear();
    iceballCPU.clear();
    shieldCPU.clear();

    state = playerState;
}
