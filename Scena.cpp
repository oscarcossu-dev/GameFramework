#ifndef OSK_SCENA_CPP
#define OSK_SCENA_CPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

const int WIDTH = 800;
const int HEIGHT = 600;

/// @brief Interfaccia astratta utilizzata dalle varie implementazioni
class GameObject
{
    protected:
    int x, y, width, height;
    bool enabled = true;

    public:

    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void SetPosition(int x, int y){ this->x = x; this->y = y; }
    virtual int GetX() { return x;}
    virtual int GetY() { return y;}
    virtual int GetW() { return width;}
    virtual int GetH() { return height;}
    virtual void SetEnabled(bool status){enabled = status;}
    virtual bool GetEnabled(){return enabled;}
};

class Collider
{
    public:

    static bool DetectCollision(GameObject* obj1, GameObject* obj2)
    {
        if(obj1 == nullptr || obj2 == nullptr)
        {
            return false;
        }

        //calcolo il centro del primo oggetto
        int x = obj1->GetX() + obj1->GetW()/2;
        int y = obj1->GetY() + obj1->GetW()/2;

        return CheckPointInArea(x,y, obj2);
    }

    //verifico se il punto è interno al rettangolo dell'oggetto
    static bool CheckPointInArea(int x, int y, GameObject* obj)
    {
        if( obj == nullptr) return false;

        if(x >= obj->GetX() && x <= obj->GetX() + obj->GetW())
            if(y >= obj->GetY() && y <= obj->GetY() + obj->GetH())
                return true;

        return false;

    }

};


class IBackground
{
    public:

    virtual void Update() = 0;
    virtual void Draw() = 0;
};


/// @brief Classe base che fornisce una implementazione di base per gestire la scena
class Scena
{
    protected:
    const int _maxNumObject = 100;
    std::vector<GameObject*> _gameObjects;

    public:
    virtual void AddGameObject(GameObject *pGame)
    {
        _gameObjects.push_back(pGame);
    }
    
    virtual void Update()
    {
        if( _gameObjects.size() > 0)
        {
            //for( GameObject *p : _gameObjects)
            for(auto p = _gameObjects.begin(); p != _gameObjects.end();)
            {
                if( (*p)->GetEnabled())
                {
                      (*p)->Update();
                      p++;
                }
                else
                _gameObjects.erase(p);
            }
        }
    };
    
    virtual void Draw(){

        if(_gameObjects.size() > 0)
        {
            for(auto go : _gameObjects)
            {
                if( go->GetEnabled()) 
                    go->Draw();
            }
        }
    };

    ~Scena()
    {
        _gameObjects.clear();
    }    
};

/// @brief Implementazione di GameObject specifica per la libreria SFML
class SFMLGameObject : public GameObject
{
    protected:
    sf::Drawable *_pDrawable;
    sf::Transformable *_pTransformable;
    sf::RenderWindow *_pRW;

    public:

    SFMLGameObject(sf::RenderWindow *rw, sf::Drawable *d = nullptr, sf::Transformable *t = nullptr) 
    : _pRW {rw} , _pDrawable {d}, _pTransformable {t}
    {
        if(rw == nullptr)
        {
            throw std::runtime_error("Manca la RenderWindow");
        }
    }

    virtual void Update() override
    {
        _pTransformable->setPosition(sf::Vector2f(x,y));
    }

    virtual void Draw() override
    {
        if(_pRW != nullptr && _pDrawable!= nullptr)
        {
            _pRW->draw((*_pDrawable));
        }
    }
};



class SFMLAnimatedGameObject : public SFMLGameObject
{
    protected:
    int _numFrameAnimation = 0;
    int _frameAnimationStart = 0;
    int _frameAnimationEnd = 0;
    int _currentFrame = 0;
    sf::IntRect _rect;
    sf::Texture* _pTexture;
    sf::Sprite* _sprite;

    public:
    
    SFMLAnimatedGameObject(sf::RenderWindow *rw, sf::IntRect  rect , std::string texturename, int frameAnimationStart, int frameAnimationEnd)
    :   SFMLGameObject(rw, nullptr, nullptr),
        _numFrameAnimation {frameAnimationEnd - frameAnimationStart},
        _frameAnimationStart {frameAnimationStart},
        _frameAnimationEnd {frameAnimationEnd},
        _currentFrame {-1},
        _rect {rect},
        _pTexture {new sf::Texture()}
    {
        _pTexture->loadFromFile(texturename);
        _sprite = new sf::Sprite(*_pTexture, rect);
        _pTransformable = _sprite;
        _pDrawable = _sprite;
    }

    virtual void Draw() override
    {
        _currentFrame++;
        if(_currentFrame > _numFrameAnimation)
        {
            _currentFrame = 0;
        }

        _rect.left = _frameAnimationStart + (_rect.width * _currentFrame);
        _sprite->setTextureRect(_rect);
        SFMLGameObject::Draw();
    }

};


class SFMLStaticImageBackground : public IBackground
{
    protected:
    sf::Drawable *_pDrawable;
    sf::Transformable *_pTransformable;
    sf::RenderWindow *_pRW;
    sf::Texture* _pTexture;

    public:
    SFMLStaticImageBackground(sf::RenderWindow *rw, std::string texturename)
    {
        _pRW = rw;
        sf::Texture* _pTexture = new sf::Texture();
        _pTexture->loadFromFile(texturename);
        auto sprite = new sf::Sprite(*_pTexture);
        sprite->setPosition(sf::Vector2f(0,0));
        _pTransformable = sprite;
        _pDrawable = sprite;
    }


    virtual void Update(){

    }

    virtual void Draw()
    {
        if(_pRW != nullptr && _pDrawable!= nullptr)
        {
            _pRW->draw((*_pDrawable));
        }
    }

    ~SFMLStaticImageBackground()
    {
        delete _pDrawable;
        delete _pTransformable;
        delete _pTexture;
    }
};




/// @brief SFMLScena estende la classe base Scena e fornisce una implementazione specifica per la libreia SFML
class SFMLScena: public Scena
{
    protected:
    sf::RenderWindow *ptrWindow;
    IBackground *pBackground;
    
    public: 

    SFMLScena(sf::RenderWindow *pWindow)
    {
        ptrWindow = pWindow;
    }

    void SetupBackground(std::string bgfilename)
    {
        pBackground = new SFMLStaticImageBackground(ptrWindow, bgfilename);
    }

    /*virtual void Update() override
    {
    }*/

    virtual void Draw() override
    {
        if(ptrWindow != nullptr)
        {
            if(pBackground != nullptr)
            {
                pBackground->Draw();
            }

            Scena::Draw();
        }
    }
};

#endif