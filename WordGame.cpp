//
//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
//#include <iostream>
//#include <vector>
//#include <string>
//#include <algorithm>
//#include <set>
//#include <cmath>
////#include "WordGame.h"
//
//#ifndef M_PI
//#define M_PI 3.14159265358979323846
//#endif
//
//std::vector<std::string> WordGame::validWords = {
//    "TRAIN", "RAIN", "RAN", "AIR", "TAN", "ANT", "ART", "RAT", "TIN", "NIT", "AIT", "NA", "AT", "IT", "AN"
//};
//
//WordGame::WordGame()
//    : window(sf::VideoMode(1200, 800), "Scramble Word Game"),
//    showCorrectMessage(false),
//    endGame(false),
//    points(0),
//    correctMessageDuration(1.0f) { // Duration for correct message in seconds
//
//    // Load background image
//    if (!backgroundTexture.loadFromFile("assets/images/level.png")) {
//        std::cerr << "Error loading background image\n";
//    }
//    backgroundTexture.setSmooth(true);
//    backgroundSprite.setTexture(backgroundTexture);
//    backgroundSprite.setScale(
//        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
//        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
//    );
//
//    // Load font
//    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
//        std::cerr << "Error loading font\n";
//    }
//
//    // Load correct image
//    if (!correctTexture.loadFromFile("assets/images/correct.png")) {
//        std::cerr << "Error loading correct image\n";
//    }
//    correctSprite.setTexture(correctTexture);
//    correctSprite.setPosition(100, 200); // Adjust position as needed
//
//    if (!music.openFromFile("assets/music/wordmusic.wav")) {
//        std::cerr << "Error loading music\n";
//    }
//
//    // Initialize game elements
//    std::string letters = "TRAIN";
//    size_t numLetters = letters.size();
//    float radius = std::max(100.0f, numLetters * 20.0f);
//    sf::Vector2f center(window.getSize().x / 2.0f, window.getSize().y * 0.7f);
//
//    for (size_t i = 0; i < numLetters; ++i) {
//        float angle = (i * 2 * M_PI) / numLetters;
//        sf::Vector2f position(center.x + radius * std::cos(angle), center.y + radius * std::sin(angle));
//
//        sf::CircleShape circle(30.0f);
//        circle.setFillColor(sf::Color::Red);
//        circle.setPosition(position.x - circle.getRadius(), position.y - circle.getRadius());
//        letterCircles.push_back(circle);
//
//        sf::Text letter(letters.substr(i, 1), font, 40);
//        letter.setFillColor(sf::Color::White);
//        sf::FloatRect textBounds = letter.getLocalBounds();
//        letter.setOrigin(textBounds.width / 2, textBounds.height / 2);
//        letter.setPosition(position.x, position.y - 10);
//        givenLetters.push_back(letter);
//    }
//
//    // Initialize word texts
//    for (int i = 0; i < numLetters; ++i) {
//        sf::Text wordText("", font, 60);
//        wordText.setFillColor(sf::Color::White);
//        wordText.setPosition(100 + i * 120, 100);
//        wordTexts.push_back(wordText);
//    }
//
//    // Initialize the message text
//    messageText.setFont(font);
//    messageText.setCharacterSize(60);
//    messageText.setFillColor(sf::Color::Magenta);
//    messageText.setPosition(220, 220);
//
//    // Initialize the points text
//    pointsText.setFont(font);
//    pointsText.setCharacterSize(30);
//    pointsText.setFillColor(sf::Color::Yellow);
//    pointsText.setPosition(10, 10);
//
//    updatePointsText();
//
//    music.play();
//}
//
//void WordGame::updatePointsText() {
//    pointsText.setString("Points: " + std::to_string(points));
//}
//
//bool WordGame::isValidWord(const std::string& word) {
//    return std::find(validWords.begin(), validWords.end(), word) != validWords.end();
//}
//
//bool WordGame::allWordsFound() const {
//    return points >= 5;
//}
//
//void WordGame::run() {
//    sf::Clock clock;
//    bool resetPending = false;
//    sf::Clock correctMessageClock;
//    bool levelCompleted = false;
//
//    // Load score image
//    sf::Texture scoreTexture;
//    if (!scoreTexture.loadFromFile("assets/images/SCORE.png")) {
//        std::cerr << "Error loading score image\n";
//    }
//    sf::Sprite scoreSprite(scoreTexture);
//    scoreSprite.setScale(0.9f, 0.9f); // Adjust scale as needed
//    scoreSprite.setPosition(5, 5); // Adjust position as needed
//
//    // Load level completed image
//    sf::Texture levelCompletedTexture;
//    if (!levelCompletedTexture.loadFromFile("assets/images/levelcomp.png")) {
//        std::cerr << "Error loading level completed image\n";
//    }
//    sf::Sprite levelCompletedSprite(levelCompletedTexture);
//    levelCompletedSprite.setPosition(200, 200); // Adjust position as needed
//
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//
//            if (!endGame && event.type == sf::Event::MouseButtonPressed) {
//                for (size_t i = 0; i < letterCircles.size(); ++i) {
//                    if (letterCircles[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
//                        clickedLetters.push_back(givenLetters[i].getString());
//                        break;
//                    }
//                }
//            }
//
//            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
//                std::string currentWord;
//                for (const auto& letter : clickedLetters) {
//                    currentWord += letter;
//                }
//
//                if (!currentWord.empty()) {
//                    if (isValidWord(currentWord) && foundWords.find(currentWord) == foundWords.end()) {
//                        foundWords.insert(currentWord);
//                        showCorrectMessage = true;
//                        correctMessageClock.restart();
//                        points++;
//                        updatePointsText();
//
//                        std::cout << "Correct word: " << currentWord << std::endl;
//                    }
//                    else {
//                        showCorrectMessage = false;
//
//                        std::cout << "Invalid word: " << currentWord << std::endl;
//                    }
//
//                    if (allWordsFound()) {
//                        endGame = true;
//                        showCorrectMessage = true;
//                        levelCompleted = true; // Set level completed flag
//                        std::cout << "Game Over: You found all words!" << std::endl;
//                    }
//
//                    for (auto& wordText : wordTexts) {
//                        wordText.setString("");
//                    }
//
//                    clickedLetters.clear();
//                    resetPending = true;
//                    clock.restart();
//                }
//            }
//        }
//
//        if (resetPending && clock.getElapsedTime().asSeconds() >= 2.0f && !endGame) {
//            resetPending = false;
//            clickedLetters.clear();
//        }
//
//        // Hide the correct message after the duration has passed
//        if (showCorrectMessage && correctMessageClock.getElapsedTime().asSeconds() >= correctMessageDuration) {
//            showCorrectMessage = false;
//        }
//
//        window.clear();
//        window.draw(backgroundSprite);
//
//        // Draw given letters
//        for (const auto& letter : givenLetters) {
//            window.draw(letter);
//        }
//
//        // Draw word texts
//        for (size_t i = 0; i < wordTexts.size(); ++i) {
//            if (i < clickedLetters.size()) {
//                wordTexts[i].setString(clickedLetters[i]);
//            }
//            window.draw(wordTexts[i]);
//        }
//
//        // Draw score image and points
//        window.draw(scoreSprite);
//        sf::Text pointsDisplay(std::to_string(points), font, 30);
//        pointsDisplay.setPosition(scoreSprite.getPosition().x + scoreSprite.getGlobalBounds().width + 10, scoreSprite.getPosition().y);
//        window.draw(pointsDisplay);
//
//        // Draw "level completed" image if level completed
//        if (levelCompleted) {
//            window.draw(levelCompletedSprite);
//        }
//
//        if (showCorrectMessage) {
//            window.draw(correctSprite);
//        }
//
//        window.display();
//        if (endGame) {
//            music.stop();
//        }
//    }
//}
