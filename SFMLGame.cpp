#include "SFMLGame.h"


// Costruttore
SFMLGame::SFMLGame(int w, int h) : Game(w,h)
{
    // Inizializzazione dei membri specifici per SFMLGame
}

// Distruttore
SFMLGame::~SFMLGame()
{
    CleanupScene();
}


void SFMLGame::Init()
{
    pWindow = new sf::RenderWindow(sf::VideoMode(Width, Height), "SFML_window");
    pWindow->setFramerateLimit(_fps);
    _pScena = new SFMLScena(pWindow);
    _Initialized = true;
}

void SFMLGame::Loop()
{

    if(pWindow == nullptr || _pScena == nullptr)
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
            ManageEvent(event);
        }
        //mutex.unlock();
        if(_Running)
        {
            // mutex.lock();
            _pScena->Update();
            pWindow->clear();
            _pScena->Draw();
            pWindow->display();
            // mutex.unlock();
        }
        //sf::sleep(sf::milliseconds(_threadWait));
    }
}


void SFMLGame::ManageEvent(sf::Event event)
{   
    if(_Running)
    {
        if (event.type == sf::Event::Closed)
        {
            _Running = false;
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

// // Metodo per l'inizializzazione della scena
// void SFMLGame::InitializeScene()
// {
//     if (_Initialized)
//         return;
    
//     Init(); // Chiamata all'override di Init nella classe Game
//     _pScena->SetWindow(pWindow); // Assicurati che la scena sia collegata al window SFML
// }

// Metodo per avviare il thread SFML
void SFMLGame::StartThread()
{
    if (_ThreadStarted)
        return;
    
    // _thread.launch(); // Commentato per evitare problemi di sincronizzazione
    // In alternativa, puoi implementare un thread manualmente se necessario
}

// Metodo per fermare il thread SFML
void SFMLGame::StopThread()
{
    if (!_ThreadStarted)
        return;
    
    _ThreadStarted = false;
    // thread.terminate(); // Commentato per evitare problemi di sincronizzazione
}

// Controllo stato di inizializzazione
bool SFMLGame::IsInitialized() const
{
    return _Initialized;
}

// Controllo stato del thread
bool SFMLGame::IsThreadRunning() const
{
    return _ThreadStarted && _Running;
}

// Implementazione CleanupScene (aggiunta per gestione scena)
void SFMLGame::CleanupScene()
{
    if (_pScena != nullptr) {
        delete _pScena;
        _pScena = nullptr;
    }
}