#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "bola.hpp"
using namespace sf;
using namespace std;

class Vaca : public Bola
{
public:
    Vaca() : Bola(1415, 144, 725, 1)
    {

        if (!shapeTexture.loadFromFile("sprites/vaca.png"))
        {
            cout << "Error loading texture" << endl;
        }
        shape.setTexture(shapeTexture);

        shape.setScale(0.17, 0.17);
        shape.setPosition(400, 40);
    }
};