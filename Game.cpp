#include "Scena.cpp"
#include <SFML/Window/Keyboard.hpp>

class Game
{
    protected:
    Scena *_pScena = nullptr;

    public:

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

class SFMLGame : public Game
{
    protected:
    sf::RenderWindow *pWindow = nullptr;
    SFMLScena *pScena = nullptr;
    bool _Initialized = false;
    public: 
    int Width, Height;

    SFMLGame(int w = 800, int h=600)
    {
        Width = w;
        Height = h;
    }

    virtual ~SFMLGame()
    {
        if(_Initialized)
        {
            delete pWindow;
            pWindow = nullptr;
        }
    }

    virtual void Init() override
    {
        pWindow = new sf::RenderWindow(sf::VideoMode(Width, Height), "SFML_window");
        pWindow->setFramerateLimit(60);
        pScena = new SFMLScena(pWindow);
        _Initialized = true;
    }

    virtual void Loop() override
    {

        if(pWindow == nullptr || pScena == nullptr)
            return;

        // The Game Loop

        while (pWindow->isOpen())
        {
            sf::Event event;
            while (pWindow->pollEvent(event))
            {
               ManageEvent(event);
            }

            pScena->Update();
            pWindow->clear();
            pScena->Draw();
            pWindow->display();
        }
    }

    virtual void ManageEvent(sf::Event event)
    {
        if (event.type == sf::Event::Closed)
                    pWindow->close();
                
        if( event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
                case sf::Keyboard::Key::Escape:
                    pWindow->close();
                break;
                
                default:
                break;
            }
        }
    }
};