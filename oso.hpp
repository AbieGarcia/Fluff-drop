#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "bola.hpp"
using namespace sf;
using namespace std;

class Oso : public Bola
{
public:
    Oso() : Bola(1357, 150, 680, 3)
    {

        if (!shapeTexture.loadFromFile("sprites/oso.png"))
        {
            cout << "Error loading texture" << endl;
        }
        shape.setTexture(shapeTexture);

        shape.setScale(0.27, 0.27);
        shape.setPosition(400, 40);
    }
};