#include "libraries.h"
#include "Graphics.h"

using std::string;

//if you want your window to move size you can delete
#define WINDOWWIDTH 400
#define WINDOWHEIGHT 400

int main(void)
{


    sf::RenderWindow window(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Game");

    

    while (window.isOpen())
    {
        sf::Event event;

        // Game Loop

        

        // /Game Loop End/

        while (window.pollEvent(event))
        {

            // Event Loop
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left)
            {
            }
            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::R)
            {
            }

            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
            // /Event Loop End/
        }


        window.display();
    }
    return 0;
}
