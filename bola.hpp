#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>
using namespace sf;
using namespace std;

class Bola
{
public:
    bool seguir;
    bool active;
    bool droped;
    Vector2f speed;
    Sprite shape;
    Texture shapeTexture;
    int limit;
    int id;
    int cursorD;
    int cursorI;

    Bola(int lim, int D, int I, int id);

    void toggleSeguir();
    void gravity();
    void friction();
    bool limits(RectangleShape limit);
    void update(RenderWindow &window, vector<Bola *> bolas, Sprite maquina);
    float getSize();
    void resvalar(vector<Bola *> bolas);
    int getCenterX();
    int getCenterY();
    void eliminar(vector<Bola *> &bolas, int &score);
    void combinar(vector<Bola *> &bolas);
    void perder(bool &lose, Sprite maquina);
};