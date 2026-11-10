#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>
#include "esfera.hpp"
using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(VideoMode(600, 400), "SFML works!");
    window.setFramerateLimit(60);

    vector<Esfera *> esferas;
    esferas.push_back(new Esfera());

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                for (auto e : esferas)
                {
                    delete e;
                }
                window.close();
            }

            if (event.type == Event::KeyPressed)
            {
                esferas[0]->move(event.key.code, true);
            }

            if (event.type == Event::KeyReleased)
            {
                esferas[0]->move(event.key.code, false);
            }
        }

        for (auto e : esferas)
            e->update();

        window.clear();
        for (auto e : esferas)
            window.draw(e->shape);
        window.display();
    }

    for (auto e : esferas)
    {
        delete e;
    }
    return 0;
}