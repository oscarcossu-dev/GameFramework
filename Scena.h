#ifndef OSK_SCENA_H
#define OSK_SCENA_H


#include"GameObject.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

const int WIDTH = 800;
const int HEIGHT = 600;

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