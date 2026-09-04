#ifndef SFMLGAME_H
#define SFMLGAME_H

#include "Game.cpp"
#include <SFML/Graphics.hpp>


class SFMLGame : public Game
{
    protected:
        // Commented out for now, but can be uncommented if needed
        //SFMLScena *pScena = nullptr;
        //sf::Thread thread;
        // sf::Mutex mutex;
        bool _Initialized = false;
        bool _ThreadStarted = false;
        bool _Running = true;
        int _threadWait = 1000 / 60;
        int _fps = 30;
        sf::RenderWindow *pWindow = nullptr;

    public:
        SFMLGame(int w, int h);
        ~SFMLGame();

        // Metodi specifici per la gestione dell'SFML
        //void InitializeScene();
        void Init() override;
        void Loop() override;
        virtual void ManageEvent(sf::Event event);
        void StartThread();
        void StopThread();
        bool IsInitialized() const;
        bool IsThreadRunning() const;

    private:
        void CleanupScene();
};

#endif // SFMLGAME_H