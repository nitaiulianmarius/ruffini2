#ifndef VECTOR2D
#define VECTOR2D

#include <SFML/Graphics.hpp>
#include <iostream>
#include "time.h"
#include "math.h"

class Vector2d
{
public:

    void setVector(sf::Vector2f i, sf::Vector2f f)
    {
        punctInitial = i;
        punctFinal = f;
        lungime = sqrt( pow(f.x - i.x, 2) + pow(f.y - i.y, 2) );
        vectorDeplasare = f-i;
        vectorNormalizat = vectorDeplasare / lungime;
    };
    void update(float &x, float &y, float v, int &lastUpdate)
    {
        float vx, vy;
        vx = vectorNormalizat.x;
        vy = vectorNormalizat.y;
        vx *= (v*(clock()-lastUpdate)/1000.);
        vy *= (v*(clock()-lastUpdate)/1000.);
        lastUpdate = clock();
        x += vx;
        y += vy;
    };
    sf::Vector2f punctInitial;
    sf::Vector2f punctFinal;
    sf::Vector2f vectorDeplasare;
    sf::Vector2f vectorNormalizat;
    float lungime;

};

#endif // VECTOR2D
