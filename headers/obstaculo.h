
using namespace sf;
using namespace std;

class Obstaculo
{
private:
    Texture txt;
    Sprite spr;
    RectangleShape * box;
    int recorte_x, recorte_y;
public:
    Obstaculo();
    void Move(float speed);
    int getX2(){int x2 = spr.getTextureRect().width+spr.getPosition().x; return x2;}
    Sprite getSprite(){return spr;}
    RectangleShape getBoxShape(){return *box;}

    FloatRect getBox(){return box->getGlobalBounds();}
    bool getCollision(FloatRect box2){return box->getGlobalBounds().intersects(box2);}
};

Obstaculo::Obstaculo()
{
    int num_spr = rand() % 8;

    txt.loadFromFile("images/velociraptorX2.png");
    spr.setTexture(txt);
    spr.setTextureRect({ spr.getTextureRect().width/8.f *num_spr , 0 , spr.getTextureRect().width/8.f , spr.getTextureRect().height });

    recorte_x = 50;
    recorte_y = 25;

    box = new RectangleShape(Vector2f(spr.getGlobalBounds().width-recorte_x, spr.getGlobalBounds().height-recorte_y));
    box->setFillColor(Color::Transparent);
    box->setOutlineColor(Color::Red);
    box->setOutlineThickness(1.1);

    spr.setPosition( 1336 , 600-spr.getGlobalBounds().height );
    box->setPosition( spr.getPosition().x+recorte_x/2.f , spr.getPosition().y+recorte_y/2.f );
}

void Obstaculo::Move(float speed)
{
    spr.move(-speed, 0);
    box->move(-speed, 0);
}
