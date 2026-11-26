#ifndef OSK_GAME_H
#define OSK_GAME_H

#include "Scena.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System.hpp>

class Game
{
    protected:
    Scena *_pScena = nullptr;

    public:
    int Width, Height;
    GameState State;
    

    Game(int w, int h): Width(w), Height(h), State(GameState::Play) {};
    
    virtual void Init() = 0;
    virtual void Loop() = 0;
    virtual ~Game()
    {
        if(_pScena != nullptr)
        {
            delete _pScena;
            _pScena = nullptr;
        }
    }
};
#endif