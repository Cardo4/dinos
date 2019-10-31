
#include "obstaculo.h"
#include "runner.h"
#include "game2.h"

using namespace sf;
using namespace std;

class Game1
{
private:

    bool GameOver;
    RenderWindow * window;
    int fps;

    Event * evento;
    bool keydown;

    Runner * rex;
    Obstaculo * obs;
    bool slot_obs;

    Texture screentxt;
    Sprite screenspr;
    int rgb;

    float frames1, framescount1;
    float frames2, framescount2;
    float speed;

public:
    Game1(Vector2u tam, std::string titulo);
    void Eventos();
    void Obstaculos();
    void Dibujar();
    void Colisiones();
    void Loop();

};

Game1::Game1(Vector2u tam, std::string titulo)
{
    GameOver=false;
    fps = 60;

    window = new RenderWindow(VideoMode(tam.x, tam.y), titulo);
    window->setFramerateLimit(fps);

    evento = new Event;
    keydown = false;

    rex = new Runner();
    obs = NULL;
    slot_obs = false;

    screentxt.loadFromFile("images/pres.png");
    screenspr.setTexture(screentxt);
    screenspr.scale(0.5, 0.5);
    screenspr.setPosition(1,1);
    rgb = 255;


    speed = 15;
    frames1 = frames2 = 0;
    framescount1 = 7;
    framescount2 = 120;

    Loop();
}

void Game1::Eventos()
{
    while(window->pollEvent(*evento))
    {
        switch(evento->type)
        {
        case Event::Closed:
            window->close();
            break;

        case Event::KeyPressed:
            switch(evento->key.code)
            {
            case Keyboard::Up:
                if(!keydown)
                {
                    rex->StartJump();
                }
                break;
            }
            break;
        }
    }
}

void Game1::Obstaculos()
{
    if(frames2 >= framescount2)
    {
        frames2-= framescount2;

        if(!slot_obs)
        {
            //short prob = 1 + rand() % (101 - 1);

            //if(prob <= 70)
            //{
            obs = new Obstaculo();
            slot_obs = true;
            //}
        }
    }

    if(obs)
    {
        obs->Move(speed);

        if(obs->getX2() <= 0)
        {
            obs = NULL;
            slot_obs = false;
        }
    }
}

void Game1::Dibujar()
{
    window->clear(Color::Black);

    rex->Move(window->getSize().y);
    window->draw(rex->getSprite());
    window->draw(rex->getBoxShape());

    window->draw(screenspr);
    if(rgb > 50)
        rgb--;
    Color wea(rgb, rgb, 200);
    screenspr.setColor(wea);

    if(obs)
    {
        window->draw(obs->getSprite());
        window->draw(obs->getBoxShape());
    }

    window->display();
}

void Game1::Colisiones()
{
    if(obs)
    {
        if( rex->getCollision(obs->getBox()) )
        {
            //GameOver = true;
        }
    }
}

void Game1::Loop()
{
    while(!GameOver)
    {
        speed+= 0.01;
        if(speed > 60)
            speed = 60;

        frames1++;
        if(framescount2>10)
            framescount2-= 0.01;
        frames2++;

        if(frames1 > framescount1)
        {
            frames1-= framescount1;
            rex->Walk();
        }

        Eventos();

        Obstaculos();

        Dibujar();

        Colisiones();
    }
}
