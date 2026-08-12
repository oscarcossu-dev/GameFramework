#include <vector>
#include "Game.cpp"
#include <cstdlib>
#include <iostream>
#include <chrono>


class SFMLGOPlayer : public SFMLGameObject
{
    int delta_movement = 5;
    
    public:
    
    SFMLGOPlayer(sf::RenderWindow *rw):SFMLGameObject(rw)
    {
        auto *pshape = new sf::RectangleShape(sf::Vector2f(20, 5));
        pshape->setFillColor(sf::Color::Blue);
        _pDrawable = pshape;
        _pTransformable = pshape;
        width = pshape->getSize().x;
        height = pshape->getSize().y;
    }

    void InputBehaviour(sf::Event event)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        //if(/*event.type == sf::Event::KeyPressed && */event.key.code == sf::Keyboard::Key::Left)
        {   
            if( x - delta_movement > 0)
                x -= delta_movement;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        //if(/*event.type == sf::Event::KeyPressed && */ event.key.code == sf::Keyboard::Key::Right)
        {  
            if(x + delta_movement + this->width < WIDTH) 
            x += delta_movement;
        }
    }
};


class SFMLGOBullet : public SFMLGameObject
{
    int delta_movement = -5;
    public:

    SFMLGOBullet(sf::RenderWindow *rw):SFMLGameObject(rw)
    {
        sf::CircleShape *shape = new sf::CircleShape(3.f);
        shape->setFillColor(sf::Color::Yellow);
        _pDrawable = shape;
        _pTransformable = shape;
        width = shape->getRadius();
        height = shape->getRadius();
    }

    virtual void Update() override
    {   
        if(y > -20)
        {
            y += delta_movement;
            SFMLGameObject::Update();
        }
    }
};

class SFMLGOEnemy : public SFMLGameObject
{
    int xr = 0,xl = 0;
    int direction = 1;
    public:

    SFMLGOEnemy(sf::RenderWindow *rw):SFMLGameObject(rw)
    {
        auto *shape = new sf::RectangleShape(sf::Vector2f(40,40));
        shape->setFillColor(sf::Color::Red);
        _pDrawable = shape;
        _pTransformable = shape;
        int rand_num = rand() % 10;
        if(!(rand_num % 2))
            direction = -1;
        width = shape->getSize().x;
        height = shape->getSize().y;
    }


    virtual void Update() override
    {
        if(xr==0)
        {
            xr = x + 10;
            xl = x -10;
        }

        if(direction > 0 )
        {
            if(x < xr)
                x++;
            else
                direction = -1;
        }
        else if(direction < 0)
        {
            if(x > xl)
                x--;
            else
                direction = 1;
        }
        SFMLGameObject::Update();
    }
};


class SFMLGameTest1Scena : public SFMLScena
{
    std::vector<SFMLGOBullet*> _bullets;
    std::vector<SFMLGOEnemy*> _enemies;
    std::chrono::steady_clock::time_point  _tLastBulletShot = std::chrono::steady_clock::now();
    const int _tDeltaBullets = 250;

    public:
    SFMLGameTest1Scena(sf::RenderWindow *window) : SFMLScena(window)
    {}

    void AddBullet(int x, int y)
    {
        std::chrono::steady_clock::time_point  now = std::chrono::steady_clock::now();

        if( std::chrono::duration_cast<std::chrono::milliseconds>(now - _tLastBulletShot).count() > _tDeltaBullets)
        {
            SFMLGOBullet *p = new SFMLGOBullet(ptrWindow);
            p->SetPosition(x,y);
            _bullets.push_back(p);
            _tLastBulletShot = now;
        }
    }

    void AddEnemy(SFMLGOEnemy *pObj)
    {
        if(pObj != nullptr)
        {
            _enemies.push_back(pObj);
        }
    }

    virtual void Update() override
    {
        SFMLScena::Update();
        int i = 0;
        for(auto elem = _bullets.begin(); elem != _bullets.end();)
        {
            auto p = *elem;
            i++;
            if(p->GetY() < 0)//il proiettile va oltre il bordo superiore dello schermo
            {
                _bullets.erase(elem);
                delete p;
            }
            else 
            {
                for(auto go = _enemies.begin(); go != _enemies.end();go++)//controllo la collisione del proiettile con i nemici
                {
                    if((*go)->GetEnabled() && Collider::DetectCollision(p,(*go)))
                    {
                        (*go)->SetEnabled(false);
                        _bullets.erase(elem);
                        delete p;
                        p = nullptr;
                        break;
                    }
                }
                if(p != nullptr) 
                {
                    p->Update();
                    elem++;
                }
            }
        }
        std::cout<<"Bullets count:"<<i<<std::endl;
        for(auto enemy : _enemies)
        {
            if(enemy->GetEnabled())
                enemy->Update();
        }
    }

    virtual void Draw() override{

        SFMLScena::Draw();
        if(_bullets.size() > 0)
        {
            for(auto bullet : _bullets)
            {
                if( bullet->GetEnabled())
                    bullet->Draw();
            }
        }

        if(_enemies.size() > 0)
        {
            for(auto enemy : _enemies)
            {
                if( enemy->GetEnabled())
                    enemy->Draw();
            }
        }
    };
};


class SFMLGameTest1 : public SFMLGame
{   
    sf::Sprite *pSprite = nullptr;
    SFMLGOPlayer *pPlayer = nullptr;

    public:
    SFMLGameTest1(int w = WIDTH, int h=HEIGHT) : SFMLGame(w,h)
    {        
    }

    virtual ~SFMLGameTest1()
    {
        if(_Initialized)
        {
            delete pSprite;
            pSprite = nullptr;
            delete pPlayer;
            pPlayer = nullptr;
        }
    }

    virtual void Init() override
    {
        SFMLGame::Init();

        delete pScena;
        pScena = new SFMLGameTest1Scena(pWindow);
        pScena->SetupBackground("bg.jpg");

        //sf::CircleShape *shape = new sf::CircleShape(100.f);
        //shape->setFillColor(sf::Color::Green);
        // sf::Texture *texture = new sf::Texture();
        // texture->loadFromFile("ball.bmp");
        // pSprite =  new sf::Sprite(*texture);
        // pSprite->setPosition(sf::Vector2f(50,50));
        //SFMLGameObject *go1 = new SFMLGameObject(pWindow, shape, shape);
        //SFMLGameObject *go2 = new SFMLGameObject(pWindow, pSprite, pSprite);
        //pScena->AddGameObject(go1);
        //pScena->AddGameObject(go2);
        
        pPlayer = new SFMLGOPlayer(pWindow);
        pPlayer->SetPosition(390, 550);
        pScena->AddGameObject(pPlayer);

        // auto test = new SFMLGOBullet(pWindow);
        // test->SetPosition(400,300);
        // pScena->AddGameObject(test);
        int distanza = 100;
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 7; j++)
            {
                auto test = new SFMLGOEnemy(pWindow);
                test->SetPosition(j*distanza + distanza, i*distanza + distanza);
                ((SFMLGameTest1Scena*)pScena)->AddEnemy(test);
            }
    }

    virtual void ManageEvent(sf::Event event) override
    {
        SFMLGame::ManageEvent(event);
        pPlayer->InputBehaviour(event);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        //if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
        //if(event.key.code == sf::Keyboard::Space)
        {
            ((SFMLGameTest1Scena*)pScena)->AddBullet(pPlayer->GetX()+20, pPlayer->GetY());
        }
    }
};