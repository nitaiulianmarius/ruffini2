#include"pauseState.h"
#include"menuState.h"
#include <stdio.h>
#include <ctime>

void pauseState::handleEvent(sf::RenderWindow* window,std::vector<stateMachine*>& currentState)
{
    while(window->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            window->close();

        if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            int numberOfButton = button.size();
            for(int i=0;i<numberOfButton;i++)
        if(button[i]->state == BUTTON_PRESSED_STATE)
                {
                    if(button[i]->mString == "Resume")
                    {
                        delete currentState[currentState.size()-1];
                        currentState.pop_back();
                    }

                    if(button[i]->mString == "Save game")
                    {
                        FILE *f = fopen("data/save/save.ini", "r");
                        int n;
                        fscanf(f,"%d",&n);
                        fclose(f);
                        if(n>=5)
                        {
                            fullSlot = true;
                            fullSlotTime = clock();
                        }
                        else
                        {
                            FILE *f = fopen("data/save/save.ini", "w");
                            fprintf(f,"%d",n+1);
                            fclose(f);
                            FILE *g = fopen("data/save/save.cfg", "a");
                            const time_t t = time(NULL);
                            tm *mTime = localtime(&t);

                            fprintf(g, "%d-%d-%d.%d.%d.%d %d %d\n",
                                    mTime->tm_mday,mTime->tm_mday,mTime->tm_year+1900,
                                    mTime->tm_hour,mTime->tm_min,mTime->tm_sec,
                                    win, lose);
                            fclose(g);
                            saved = true;
                            saveTime = clock();
                        }
                    }

                    if(button[i]->mString == "Return to main menu")
                    {
                        for(int i=currentState.size()-1;i>0;i--)
                        {
                            delete currentState[i];
                            currentState.pop_back();
                        }
                        backgroundMusic.stop();
                    }
                    if(button[i]->mString == "Quit")
                    {
                        window->close();
                    }
                }
        }

    }
}

void pauseState::update(sf::RenderWindow* window,std::vector<stateMachine*>& currentState)
{

    int numberOfButton = button.size();
    for(int i=0;i<numberOfButton;i++)
        button[i]->update(window, currentState);
}

void pauseState::render(sf::RenderWindow*& window)
{
    int numberOfButton = button.size();
    for(int i=0;i<numberOfButton;i++)
        button[i]->render(window);
    if(saved && clock()-saveTime<700)
        outtextxy(window, window->getSize().x/2-30, window->getSize().y/2-30, "Saved!\n", sf::Color(0,255,0,255),30);
    if(clock()-saveTime >=700)
        saved = false;

    if(fullSlot && clock()-fullSlotTime<1000)
        outtextxy(window, window->getSize().x/2-60, window->getSize().y/2-60, "Not enough space\n", sf::Color(255,0,0,255),30);
    if(clock()-fullSlotTime >= 1000)
        fullSlot = false;
}
