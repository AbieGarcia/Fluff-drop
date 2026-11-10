#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "bola.hpp"
using namespace sf;
using namespace std;

class Cat : public Bola
{
public:
    Cat() : Bola(1445, 150, 760, 0)
    {

        if (!shapeTexture.loadFromFile("sprites/cat.png"))
        {
            cout << "Error loading texture" << endl;
        }
        shape.setTexture(shapeTexture);

        shape.setScale(0.12, 0.12);
        shape.setPosition(400, 40);
    }
};
