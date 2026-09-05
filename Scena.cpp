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
                    p = _gameObjects.erase(p);
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

#endif