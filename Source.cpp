#include <SFML/Graphics.hpp>
#include "mission1.h"
#include "FirstPage.h"


int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Title", sf::Style::Close);
    window.setFramerateLimit(60);

   
    FirstPage firstPage(window);

   
    firstPage.run();

   
    if (firstPage.gameStarted()) {
       
        mission1 game;

      
        game.run();
    }

    return 0;
}



