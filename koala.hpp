#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "bola.hpp"
using namespace sf;
using namespace std;

class Koala : public Bola
{
public:
    Koala() : Bola(1396, 150, 680, 2)
    {

        if (!shapeTexture.loadFromFile("sprites/koala.png"))
        {
            cout << "Error loading texture" << endl;
        }
        shape.setTexture(shapeTexture);

        shape.setScale(0.25, 0.2);
        shape.setPosition(400, 40);
    }
};