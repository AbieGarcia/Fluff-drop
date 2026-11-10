#include "bola.hpp"

Bola::Bola(int lim, int D, int I, int id) : id(id)
{
    seguir = true;
    active = true;
    speed.x = 0;
    speed.y = 10;
    limit = lim;
    cursorD = D;
    cursorI = I;
    droped = 0;
}

void Bola::toggleSeguir()
{
    seguir = !seguir;
}

void Bola::gravity()
{
    speed.y += 0.2;
}
void Bola::friction()
{
    if (speed.x > 0)
    {
        speed.x -= 0.3;
    }
    else if (speed.x < 0)
        speed.x += 0.3;
}

float Bola::getSize()
{
    return shape.getLocalBounds().getSize().y;
}

void Bola::update(RenderWindow &window, vector<Bola *> bolas, Sprite maquina)
{
    Vector2f pos = shape.getPosition();
    if (seguir)
    {
        Vector2i mousePos = Mouse::getPosition(window);
        if (mousePos.x > cursorD && mousePos.x < cursorI)
        {
            shape.setPosition(static_cast<float>(mousePos.x) - 50, 40);
        }
    }
    else
    {
        if (speed.y != 0)
            gravity();
        if (speed.x != 0)
            friction();
        for (auto b : bolas)
        {
            if (b != this || b != bolas.back())
            {
                if (!b->active)
                    continue;

                if (shape.getGlobalBounds().intersects(b->shape.getGlobalBounds()))
                {
                    resvalar(bolas);
                }
            }
        }
    }
    if (shape.getPosition().x < cursorI || shape.getPosition().x > cursorD)
    {
        if (!seguir)
            shape.move(speed);
    }
    if (pos.y + getSize() > limit)
    {
        shape.setPosition(pos.x, limit - getSize());
        speed.y *= -0.4;
    }
    if (pos.y < limit)
    {
        if (pos.y > maquina.getPosition().y + maquina.getGlobalBounds().getSize().y)
        {
            if (!droped)
            {
                droped = 1;
            }
        }
        else if (pos.y > maquina.getPosition().y)
        {
            for (auto b : bolas)
            {
                if (b == this || b == bolas.back())
                {
                    continue;
                }
                if (!b->active)
                {
                    continue;
                }
                if (shape.getGlobalBounds().intersects(b->shape.getGlobalBounds()))
                {
                    if (!droped)
                    {
                        droped = 1;
                    }
                }
            }
        }
    }
}

void Bola::resvalar(vector<Bola *> bolas)
{

    for (auto &b : bolas)
    {

        if (b == this || b == bolas.back())
            continue;

        if (shape.getGlobalBounds().intersects(b->shape.getGlobalBounds()))
        {
            if (shape.getPosition().x < b->shape.getPosition().x - shape.getGlobalBounds().getSize().x + 40)
            {
                speed = {-2, 1};
            }
            else if (shape.getPosition().x > b->shape.getPosition().x + b->shape.getGlobalBounds().getSize().x - 40)
            {

                speed = {2, 1};
            }
            else
            {
                speed = {0, 0};
            }
        }
    }
}
bool Bola::limits(RectangleShape limit)
{
    if (shape.getPosition().x + shape.getGlobalBounds().width > limit.getPosition().x + 700 || shape.getPosition().x < limit.getPosition().x)
        return 1;
    else
        return 0;
}

int Bola::getCenterX()
{
    return shape.getPosition().x + shape.getLocalBounds().width / 2;
}
int Bola::getCenterY()
{
    return shape.getPosition().y + shape.getLocalBounds().height / 2;
}

void Bola::eliminar(vector<Bola *> &bolas, int &score)
{
    for (auto &b : bolas)
    {
        if (b == this || b->shape.getPosition().y < 150)
            continue;
        if (shape.getGlobalBounds().intersects(b->shape.getGlobalBounds()))
        {
            if (this->id == b->id)
            {
                b->active = false;
                switch (id)
                {
                case 0: // Cat
                    if (!shapeTexture.loadFromFile("sprites/vaca.png"))
                    {
                        cout << "Error loading texture" << endl;
                    }
                    shape.setTexture(shapeTexture);

                    shape.setScale(0.17, 0.17);
                    cursorD = 144;
                    cursorI = 725;
                    limit = 1415;
                    score += 10;
                    break;
                case 1: // Vaca
                    if (!shapeTexture.loadFromFile("sprites/koala.png"))
                    {
                        cout << "Error loading texture" << endl;
                    }
                    shape.setTexture(shapeTexture);

                    shape.setScale(0.25, 0.2);
                    cursorD = 150;
                    cursorI = 680;
                    limit = 1396;
                    speed = {0, 0};
                    shape.setPosition(shape.getPosition().x, shape.getPosition().y + 60);
                    score += 20;
                    break;
                case 2: // Koala
                    if (!shapeTexture.loadFromFile("sprites/oso.png"))
                    {
                        cout << "Error loading texture" << endl;
                    }
                    shape.setTexture(shapeTexture);

                    shape.setScale(0.27, 0.27);
                    cursorD = 150;
                    cursorI = 680;
                    limit = 1357;
                    if (shape.getPosition().y >= limit)

                        shape.setPosition(shape.getPosition().x, limit - shape.getGlobalBounds().height);
                    score += 30;
                    break;
                case 3: // Oso
                    if (!shapeTexture.loadFromFile("sprites/pig.png"))
                    {
                        cout << "Error loading texture" << endl;
                    }
                    shape.setTexture(shapeTexture);

                    shape.setScale(0.4, 0.4);
                    cursorD = 150;
                    cursorI = 680;
                    limit = 1285;
                    if (shape.getPosition().y >= limit)

                        shape.setPosition(shape.getPosition().x, limit - shape.getGlobalBounds().height);
                    score += 40;
                    break;
                case 4: // Pig
                    if (!shapeTexture.loadFromFile("sprites/panda.png"))
                    {
                        cout << "Error loading texture" << endl;
                    }
                    shape.setTexture(shapeTexture);

                    shape.setScale(0.7, 0.7);
                    cursorD = 150;
                    cursorI = 680;
                    limit = 1120;
                    if (shape.getPosition().x + shape.getGlobalBounds().width < cursorI - 300)
                    {
                        shape.setPosition(shape.getPosition().x - shape.getGlobalBounds().width, 560);
                    }
                    else
                    {
                        shape.setPosition(shape.getPosition().x, 560);
                    }
                    speed = {0, 0};
                    score += 50;
                    break;
                case 5: // Panda
                    score += 100;
                    this->active = false;

                default:
                    break;
                }

                if (id < 5)
                    id++;
            }
        }
    }
}

void Bola::perder(bool &lose, Sprite maquina)
{
    if (shape.getPosition().y < maquina.getPosition().y + maquina.getGlobalBounds().height - 60)
    {
        lose = 1;
    }
}
