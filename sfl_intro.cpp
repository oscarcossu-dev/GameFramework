#include "sfmlGameTest1.h"


int main()
{
    /*sf::RenderWindow window(sf::VideoMode(800, 600), "SFML_window");
    window.setFramerateLimit(60);
    SFMLScena test(&window);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    sf::Texture texture;
    texture.loadFromFile("ball.bmp");
    sf::Sprite sprite(texture);
    sprite.setPosition(sf::Vector2f(50,50));
    SFMLGameObject go1(&window, &shape, &shape),go2(&window, &sprite, &sprite);
    test.AddGameObject(&go1);
    test.AddGameObject(&go2);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if( event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::Key::Escape:
                        window.close();
                    break;
                    case sf::Keyboard::Key::Up:
                    sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y-1);
                    break;
                    case sf::Keyboard::Key::Down:
                        sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y+1);
                    break;
                    case sf::Keyboard::Key::Left:
                    sprite.setPosition(sprite.getPosition().x-1, sprite.getPosition().y);
                    break;
                    case sf::Keyboard::Key::Right:
                    sprite.setPosition(sprite.getPosition().x+1, sprite.getPosition().y);
                    break;
                    
                    default:
                    break;
                }
            }
        }

        test.Draw();
    }*/
   
    SFMLGameTest1 game;
    game.Init();
    game.Loop();
    
    return 0;
}