
using namespace sf;
using namespace std;

class Runner
{
private:
    Texture txt;
    Sprite spr;
    RectangleShape * box;
    float jumpspeed;
    bool jump;
    int recorte_x, recorte_y;
    int ns;
public:
    Runner();
    void StartJump();
    void EndJump(int floor);
    void Gravity();
    void Move(int floor);
    void Walk();
    void ChangeSprite();
    float getJumpSpeed(){return jumpspeed;}
    Sprite getSprite(){return spr;}
    RectangleShape getBoxShape(){return *box;}

    FloatRect getBox(){return box->getGlobalBounds();}
    bool getCollision(FloatRect box2){return box->getGlobalBounds().intersects(box2);}
};

Runner::Runner()
{
    txt.loadFromFile("images/velociraptorX2.png");
    spr.setTexture(txt);
    spr.setTextureRect({ 0 , 0, txt.getSize().x/8.f , txt.getSize().y });

    recorte_x = 50;
    recorte_y = 25;
    ns = 0;

    box = new RectangleShape(Vector2f(spr.getGlobalBounds().width-recorte_x , spr.getGlobalBounds().height-recorte_y));
    box->setFillColor(Color::Transparent);
    box->setOutlineColor(Color::Red);
    box->setOutlineThickness(1.1);

    spr.setPosition( 150 , 600-spr.getGlobalBounds().height );
    box->setPosition( spr.getPosition().x+recorte_x/2.f , spr.getPosition().y+recorte_y/2.f );

    jumpspeed = 0;
    jump = false;
}

void Runner::StartJump()
{
    if(!jump)
    {
        ns = 0;
        ChangeSprite();
        jumpspeed = 25;
        jump = true;
    }
}

void Runner::EndJump(int floor)
{
    if(spr.getPosition().y >= floor-spr.getGlobalBounds().height)
    {
        jump = false;
        spr.setPosition( spr.getPosition().x , floor-spr.getGlobalBounds().height );
        box->setPosition( spr.getPosition().x+recorte_x/2.f , spr.getPosition().y+recorte_y/2.f );
    }
}

void Runner::Gravity()
{
    if(jump)
        jumpspeed-= 1.2;
}

void Runner::Move(int floor)
{
    Gravity();
    spr.move(0, -jumpspeed);
    box->move(0, -jumpspeed);
    EndJump(floor);
}

void Runner::ChangeSprite()
{
    spr.setTextureRect({ txt.getSize().x/8.f *ns , 0 , txt.getSize().x/8.f , txt.getSize().y });
}

void Runner::Walk()
{
    if(!jump)
    {
        ChangeSprite();
        ns++;
        if(ns >= 7)
            ns = 0;
    }
}
