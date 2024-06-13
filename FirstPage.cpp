#include "FirstPage.h"

FirstPage::FirstPage(sf::RenderWindow& window)
    : window(window), started(false), transitionOpacity(0.0f), displayingLevelInfo(false) {
    
    if (!backgroundImage.loadFromFile("assets/images/firstpage.png")) {
        std::cerr << "Error loading background image\n";
    }
    backgroundImage.setSmooth(true);
    backgroundSprite.setTexture(backgroundImage);

    
    float scaleX = static_cast<float>(window.getSize().x) / backgroundImage.getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / backgroundImage.getSize().y;
    backgroundSprite.setScale(scaleX, scaleY);

    
    if (!font.loadFromFile("assets/fonts/Algerian.ttf")) {
        std::cerr << "Error loading font\n";
    }

    
    initializeMenu();

    
    transitionOverlay.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    transitionOverlay.setFillColor(sf::Color(0, 0, 0, 0));

   
    if (!levelInfoTexture.loadFromFile("assets/images/background.png")) {
        std::cerr << "Error loading level information image\n";
    }
    levelInfoSprite.setTexture(levelInfoTexture);
    levelInfoSprite.setScale(
        static_cast<float>(window.getSize().x) / levelInfoTexture.getSize().x,
        static_cast<float>(window.getSize().y) / levelInfoTexture.getSize().y
    );

    
    initializeBackButton();

    
    initializeLevelInfoText();
}

void FirstPage::initializeMenu() {
    
    playButton.setFillColor(sf::Color::Transparent);
    playButton.setSize(sf::Vector2f(320, 150));
    playButton.setPosition(240, 60);

    
    levelButton.setFillColor(sf::Color::Transparent);
    levelButton.setSize(sf::Vector2f(320, 150));
    levelButton.setPosition(240, 230);

    
    exitButton.setFillColor(sf::Color::Transparent);
    exitButton.setSize(sf::Vector2f(320, 150));
    exitButton.setPosition(240, 400);
}

void FirstPage::initializeBackButton() {
    
    backButton.setFillColor(sf::Color::Black); 
    backButton.setSize(sf::Vector2f(150, 60)); 
    backButton.setPosition(20, 20); 
    
    backButtonText.setFont(font);
    backButtonText.setString("Back");
    backButtonText.setCharacterSize(24); 
    backButtonText.setFillColor(sf::Color::White);
    
    sf::FloatRect textBounds = backButtonText.getLocalBounds();
    backButtonText.setOrigin(textBounds.left + textBounds.width / 2.0f,
        textBounds.top + textBounds.height / 2.0f);
    backButtonText.setPosition(backButton.getPosition().x + backButton.getSize().x / 2.0f,
        backButton.getPosition().y + backButton.getSize().y / 2.0f);
}

void FirstPage::initializeLevelInfoText() {
    
    levelInfoText.setFont(font);
    levelInfoText.setString("This is a 5 Level Game \n Credits \n Mudassar Virk \n Huzaifa Abbas \n Jawad Afridi"); 
    levelInfoText.setCharacterSize(50); 
    levelInfoText.setFillColor(sf::Color(25, 25, 112));
    
    levelInfoText.setPosition(200, 200); 
}

bool FirstPage::gameStarted() const {
    return started;
}

void FirstPage::handleMenuEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

        if (playButton.getGlobalBounds().contains(mousePos)) {
            std::cout << "Start New Game clicked!\n";
            started = true;
        }
        else if (levelButton.getGlobalBounds().contains(mousePos)) {
            std::cout << "Level Button clicked!\n";
            displayingLevelInfo = true; 
        }
        else if (exitButton.getGlobalBounds().contains(mousePos)) {
            std::cout << "Exit Game clicked!\n";
            window.close();
        }

        
        if (displayingLevelInfo && backButton.getGlobalBounds().contains(mousePos)) {
            std::cout << "Back Button clicked!\n";
            displayingLevelInfo = false; 
        }
    }
}

void FirstPage::drawMenu() {
    window.draw(backgroundSprite);
    window.draw(playButton);
    window.draw(levelButton);
    window.draw(exitButton);
}

void FirstPage::drawLevelInfo() {
    window.draw(levelInfoSprite);
    window.draw(backButton);
    window.draw(backButtonText);
    window.draw(levelInfoText); 
}

void FirstPage::applyTransition() {
    if (transitionOpacity < 255.0f) {
        transitionOpacity += 5.0f; 
        transitionOverlay.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(transitionOpacity)));
        window.draw(transitionOverlay);
    }
    else {
        window.close(); 
    }
}

void FirstPage::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            handleMenuEvent(event);
        }

       
        window.clear(sf::Color::Black);

        if (started) {
            applyTransition();
        }
        else {
            drawMenu(); 
            if (displayingLevelInfo) {
                drawLevelInfo(); 
            }
        }

        window.display();
    }
}
