#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "bola.hpp"
using namespace sf;
using namespace std;

class Panda : public Bola
{
public:
    Panda() : Bola(1120, 150, 680, 5)
    {

        if (!shapeTexture.loadFromFile("sprites/panda.png"))
        {
            cout << "Error loading texture" << endl;
        }
        shape.setTexture(shapeTexture);

        shape.setScale(0.7, 0.7);
        shape.setPosition(400, 40);
    }
};