#ifndef SFML_SCENA_H
#define SFML_SCENA_H

#include "SFMLGameObject.h"


/// @brief SFMLScena estende la classe base Scena e fornisce una implementazione specifica per la libreia SFML
class SFMLScena: public Scena
{
    protected:
    sf::RenderWindow *_ptrWindow = nullptr;
    IBackground *_pBackground = nullptr;
    
    public: 

    SFMLScena(sf::RenderWindow *pWindow)
    {
        _ptrWindow = pWindow;
    }

    void SetupBackground(std::string bgfilename)
    {
        if( _pBackground) delete _pBackground;
        _pBackground = new SFMLStaticImageBackground(_ptrWindow, bgfilename);
    }

    /*virtual void Update() override
    {
    }*/

    virtual void Draw() override
    {
        if(_ptrWindow != nullptr)
        {
            if(_pBackground != nullptr)
            {
                _pBackground->Draw();
            }

            Scena::Draw();
        }
    }
};
#endif