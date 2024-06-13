#ifndef FIRST_PAGE_H
#define FIRST_PAGE_H

#include <SFML/Graphics.hpp>
#include <iostream>

class FirstPage {
public:
    FirstPage(sf::RenderWindow& window);
    bool gameStarted() const;
    void handleMenuEvent(const sf::Event& event);
    void drawMenu();
    void drawLevelInfo();
    void applyTransition();
    void run();

private:
    sf::RenderWindow& window;
    bool started;
    bool displayingLevelInfo;
    float transitionOpacity;
    sf::Texture backgroundImage;
    sf::Sprite backgroundSprite;
    sf::Font font;
    sf::RectangleShape playButton;
    sf::RectangleShape levelButton;
    sf::RectangleShape exitButton;
    sf::RectangleShape transitionOverlay;
    sf::Texture levelInfoTexture;
    sf::Sprite levelInfoSprite;
    sf::RectangleShape backButton;
    sf::Text backButtonText;
    sf::Text levelInfoText; 

    void initializeMenu();
    void initializeBackButton();
    void initializeLevelInfoText(); 
};

#endif 
