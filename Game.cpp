#ifndef OSK_GAME_CPP
#define OSK_GAME_CPP

#include "Scena.cpp"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System.hpp>

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
    
    SFMLScena *pScena = nullptr;
    // sf::Thread thread;
    // sf::Mutex mutex;
    bool _Initialized = false;
    bool _ThreadStarted = false;
    bool _Running = true;
    int _threadWait = 1000 / 60;

    public: 
    int Width, Height;
    sf::RenderWindow *pWindow = nullptr;


    SFMLGame(int w = 800, int h=600)
    // :thread(&SFMLGame::PopEvent, this)
    {
        Width = w;
        Height = h;
    }

    virtual ~SFMLGame()
    {
        // if(_ThreadStarted)
        // {
        //     _ThreadStarted = false;
        //     thread.terminate();
        // }

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
        _Running = true;
        while (pWindow->isOpen())
        {
            // if(!_ThreadStarted)
            // {
            //     _ThreadStarted = true;
            //     thread.launch();
            // }

            //mutex.lock();
            sf::Event event;
            while (pWindow->pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                {
                    _Running = false;
                    pWindow->close();
                }
                ManageEvent(event);
            }
            //mutex.unlock();
            if(_Running)
            {
                // mutex.lock();
                pScena->Update();
                pWindow->clear();
                pScena->Draw();
                pWindow->display();
                // mutex.unlock();
            }
            //sf::sleep(sf::milliseconds(_threadWait));
        }
    }


    void PopEvent()
    {
        sf::Event event;
        while(_ThreadStarted && _Running)
        {
            while (pWindow->pollEvent(event))
            {
                ManageEvent(event);
            }
            sf::sleep(sf::milliseconds(_threadWait / 4));
        }
    }


    virtual void ManageEvent(sf::Event event)
    {   
        if(_Running)
        {
            if (event.type == sf::Event::Closed)
            {
                // mutex.lock();
                _ThreadStarted = false;
                // thread.terminate();
                pWindow->close();
                // mutex.unlock();
                return;
            }
                    
            if( event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::Key::Escape:
                        
                        _ThreadStarted = false;
                        _Running = false;
                        
                        // mutex.lock();
                        pWindow->close();
                        // mutex.unlock();
                        // thread.terminate();
                    break;
                    
                    default:
                    break;
                }
            }
        }    
    }
    
    //non utilizzato. rimuovere
    virtual void UpdateDrawThread()
    {
        while(_ThreadStarted && _Running)
        {
            // mutex.lock();
            pScena->Update();
            pWindow->clear();
            pScena->Draw();
            pWindow->display();
            // mutex.unlock();
            sf::sleep(sf::milliseconds(_threadWait));
        }
    }
};

#endif