#ifndef SFML_GAMEOBJECT_H
#define SFML_GAMEOBJECT_H

#include "Scena.cpp"
#include <SFML/Graphics.hpp>



/// @brief Implementazione di GameObject specifica per la libreria SFML
class SFMLGameObject : public GameObject
{
    protected:
    sf::Drawable *_pDrawable = nullptr;
    sf::Transformable *_pTransformable = nullptr;
    sf::RenderWindow *_pRW = nullptr;

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
    int _texturex = 0;
    int _texturey = 0;
    bool _repeat = true;
    sf::IntRect _textureRect;
    sf::Texture* _pTexture;
    sf::Sprite* _sprite;

    public:

    SFMLAnimatedGameObject(sf::RenderWindow *rw, sf::IntRect  rect , std::string texturename, int frameAnimationStart, int frameAnimationEnd, bool repeat = true)
    :   SFMLGameObject(rw, nullptr, nullptr),
        _numFrameAnimation {frameAnimationEnd - frameAnimationStart},
        _frameAnimationStart {frameAnimationStart},
        _frameAnimationEnd {frameAnimationEnd},
        _currentFrame {0},
        _textureRect {rect},
        _repeat {repeat},
        _pTexture {new sf::Texture()},
        _texturex {rect.left},
        _texturey {rect.top}
    {
        _pTexture->loadFromFile(texturename);
        _sprite = new sf::Sprite(*_pTexture, rect);
        _pTransformable = _sprite;
        _pDrawable = _sprite;
    }

    virtual void Draw() override
    {
        if(enabled)
        { 
            _textureRect.left = _texturex + (_textureRect.width * _currentFrame);
            _sprite->setTextureRect(_textureRect);
            SFMLGameObject::Draw();

            if(_currentFrame <= _numFrameAnimation )
                _currentFrame++;
            

            if(_repeat && _currentFrame > _numFrameAnimation)
            {
                _currentFrame = 0;
            }
        }
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
    : _pRW { rw}
    {
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
        if(_pDrawable) delete _pDrawable;
        if(_pTransformable) delete _pTransformable;
        if(_pTexture) delete _pTexture;
    }
};

#endif