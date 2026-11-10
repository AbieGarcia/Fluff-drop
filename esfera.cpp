#include "esfera.hpp"
#include <cmath>
using namespace std;
Esfera::Esfera() : shape(50.f), speed({0, 0})
{
    shape.setFillColor(Color::Green);
    shape.setOrigin(50, 50);
    shape.setPosition(300, 200);
}

void Esfera::update()
{
    // rebota en los bordes de la pantalla
    // cambia de color aleatorio cuando rebota.
    gravity();
    shape.move(speed);
    borders();
}

void Esfera::gravity()
{
    speed.y += 0.2; // entre más alto, más fuerte la gravedad.
}

void Esfera::borders()
{
    Vector2f pos = shape.getPosition();
    if (pos.y + shape.getRadius() > 400)
    {
        shape.setPosition(pos.x, 400 - shape.getRadius());
        speed.y *= -0.8; // qué tanto rebota.
    }
}

void Esfera::move(Keyboard::Key key, bool isPressed)
{
    if (isPressed)
    {
        if (key == Keyboard::Right)
            speed.x = 4;
        if (key == Keyboard::Left)
            speed.x = -4;
        if (key == Keyboard::Space)
            speed.y = -6;
    }
    else
    {
        if (key == Keyboard::Right)
            speed.x -= 4;
        if (key == Keyboard::Left)
            speed.x += 4;
    }
}