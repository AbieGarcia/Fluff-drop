#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "bola.hpp"
#include "cat.hpp"
#include "vaca.hpp"
#include "koala.hpp"
#include "oso.hpp"
#include "pig.hpp"
#include "panda.hpp"
using namespace sf;
using namespace std;
void reiniciar(vector<Bola *> &bolas, int &scoreNum);
int main()
{
    RenderWindow window(VideoMode(1300, 1000), "Fluff Drop");
    window.setFramerateLimit(60);

    bool lose = 0;
    int num = 0;
    int scoreNum = 0;

    // *************************SPRITES**********************************
    Sprite secuencia;
    Texture secuenciaTexture;
    if (!secuenciaTexture.loadFromFile("sprites/sequence.png"))
    {
        cout << "Error loading texture" << endl;
    }

    secuencia.setTexture(secuenciaTexture);
    secuencia.setPosition(815, 700);
    secuencia.setScale(0.6, 0.6);

    Sprite maquina;
    Texture maquinaTexture;
    if (!maquinaTexture.loadFromFile("sprites/maquina.png"))
    {
        cout << "Error loading texture" << endl;
    }

    maquina.setTexture(maquinaTexture);
    maquina.setPosition(88, 60);
    maquina.setScale(0.9, 0.6);

    // *************************TEXTOS**********************************

    Font font;
    if (!font.loadFromFile("sprites/Daydream.ttf"))
    {
        cout << "Error loading font" << endl;
    }

    Text texto("Fluff-Drop", font);
    texto.setCharacterSize(45);
    texto.setFillColor(Color(174, 96, 219));
    texto.setPosition(834, 120);

    Text score("Score", font);
    score.setCharacterSize(60);
    score.setFillColor(Color(251, 233, 103));
    score.setPosition(880, 320);

    Text numText(to_string(scoreNum), font); // marcador en num
    numText.setCharacterSize(100);
    numText.setFillColor(Color::White);
    numText.setPosition(900, 440);

    Text loseTxt("Game Over", font);
    loseTxt.setCharacterSize(60);
    loseTxt.setFillColor(Color(174, 96, 219));
    loseTxt.setPosition(328, 400);

    Text salirTxt("Salir", font);
    salirTxt.setCharacterSize(30);
    salirTxt.setFillColor(Color::White);
    salirTxt.setPosition(520, 540);

    Text reintentarTxt("Reintentar", font);
    reintentarTxt.setCharacterSize(30);
    reintentarTxt.setFillColor(Color::White);
    reintentarTxt.setPosition(450, 640);

    // *************************RECTANGULOS**********************************

    RectangleShape limit;
    limit.setSize(Vector2f(700, 800));
    limit.setFillColor(Color::Transparent);
    limit.setOutlineColor(Color(197, 247, 247));
    limit.setOutlineThickness(5);
    limit.setPosition(100, 150);

    RectangleShape rectangle;
    rectangle.setSize(Vector2f(600, 400));
    rectangle.setFillColor(Color(197, 247, 247));
    rectangle.setOutlineColor(Color(174, 96, 219));
    rectangle.setOutlineThickness(5);
    rectangle.setPosition(300, 350);

    RectangleShape salirBtn;
    salirBtn.setSize(Vector2f(400, 80));
    salirBtn.setFillColor(Color(251, 233, 103));
    salirBtn.setOutlineColor(Color(255, 205, 253));
    salirBtn.setOutlineThickness(5);
    salirBtn.setPosition(400, 520);

    RectangleShape reintentarBtn;
    reintentarBtn.setSize(Vector2f(400, 80));
    reintentarBtn.setFillColor(Color(251, 233, 103));
    reintentarBtn.setOutlineColor(Color(255, 205, 253));
    reintentarBtn.setOutlineThickness(5);
    reintentarBtn.setPosition(400, 620);

    //*********************************************************************************
    vector<Bola *> bolas;

    bolas.push_back(new Cat());

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                for (auto b : bolas)
                {
                    delete b;
                }
                window.close();
            }

            if (event.type == Event::MouseButtonPressed)
            {
                Vector2i mousePos = Mouse::getPosition(window);

                if (lose)
                {
                    if (mousePos.x > reintentarBtn.getPosition().x && mousePos.x < reintentarBtn.getPosition().x + reintentarBtn.getGlobalBounds().width)
                    {
                        if (mousePos.y > reintentarBtn.getPosition().y && mousePos.y < reintentarBtn.getPosition().y + reintentarBtn.getGlobalBounds().height)
                            reiniciar(bolas, scoreNum);
                        lose = 0;
                    }
                    if (mousePos.x > salirBtn.getPosition().x && mousePos.x < salirBtn.getPosition().x + salirBtn.getGlobalBounds().width)
                    {
                        if (mousePos.y > salirBtn.getPosition().y && mousePos.y < salirBtn.getPosition().y + salirBtn.getGlobalBounds().height)
                        {
                            for (auto b : bolas)
                            {
                                delete b;
                            }
                            window.close();
                        }
                    }
                }
                else
                {

                    for (auto b : bolas)
                    {
                        if (b->seguir == true)
                        {
                            b->toggleSeguir();
                        }
                    }

                    num = rand() % 2;

                    switch (num)
                    {
                    case 0:
                        bolas.push_back(new Cat());
                        break;

                    case 1:
                        bolas.push_back(new Vaca());
                        break;

                    default:
                        break;
                    }
                }
            }
        }

        for (auto bol : bolas)
        {

            if (bol->limits(limit))
            {
                bol->speed.x = -bol->speed.x;

                bol->shape.move(bol->speed);
            }
            else
            {
                if (bol->shape.getPosition().y > bol->limit)
                    bol->speed = {0, 0};
                bol->update(window, bolas, maquina);
                bol->eliminar(bolas, scoreNum);
                if (bol->droped)
                {
                    bol->perder(lose, maquina);
                }
            }
        }

        numText.setString(to_string(scoreNum));

        bolas.erase(remove_if(bolas.begin(), bolas.end(), [](Bola *b)
                              {
    if (!b->active) {
        delete b;  
        return true;
    }
    return false; }),
                    bolas.end());

        window.clear(Color(255, 177, 223));

        for (auto b : bolas)
            window.draw(b->shape);

        window.draw(texto);
        window.draw(score);
        window.draw(numText);
        window.draw(limit);
        window.draw(secuencia);
        window.draw(maquina);

        if (lose)
        {
            window.draw(rectangle);
            window.draw(salirBtn);
            window.draw(reintentarBtn);
            window.draw(loseTxt);
            window.draw(salirTxt);
            window.draw(reintentarTxt);
        }
        window.display();
    }

    for (auto b : bolas)
    {
        delete b;
    }

    return 0;
}

void reiniciar(vector<Bola *> &bolas, int &scoreNum)
{
    scoreNum = 0;
    for (auto b : bolas)
    {
        delete b;
    }
    bolas.clear();

    bolas.push_back(new Cat());
}