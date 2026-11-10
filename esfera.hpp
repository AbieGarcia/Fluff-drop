#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
using namespace sf;
using namespace std;

class Esfera
{
public:
    CircleShape shape;
    Vector2f speed;
    Vector2i objetivo;

    Esfera();

    void update();
    void gravity();
    void borders();
    void move(Keyboard::Key key, bool isPressed);
};