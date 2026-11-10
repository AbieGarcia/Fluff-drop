#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "bola.hpp"
using namespace sf;
using namespace std;

class Pig : public Bola
{
public:
    Pig() : Bola(1285, 150, 680, 4)
    {

        if (!shapeTexture.loadFromFile("sprites/pig.png"))
        {
            cout << "Error loading texture" << endl;
        }
        shape.setTexture(shapeTexture);

        shape.setScale(0.4, 0.4);
        shape.setPosition(400, 40);
    }
};