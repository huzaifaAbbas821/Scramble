#ifndef MISSION1_H
#define MISSION1_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <SFML/Audio.hpp>
using namespace std;
class mission1 {
public:
    mission1();
    void run();

private:
    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;
    sf::Texture correctTexture;
    sf::Sprite correctSprite;
    sf::Text pointsText;
    sf::Text levelText;
    int points;
    int levels;
    sf::CircleShape mainCircle;
    vector<sf::CircleShape> letterCircles;
    vector<sf::Text> givenLetters;
    vector<sf::Text> wordTexts;
    sf::Text messageText;
    sf::Music backgroundMusic;
    bool showCorrectMessage;
    bool endGame;
    vector<std::string> clickedLetters;
    vector<std::string> correctWords;
    static std::vector<std::string> validWords;
    vector<sf::Text> rectangleLetters; 
    vector<std::vector<sf::RectangleShape>> rectangles; 
    unordered_map<std::string, std::vector<std::pair<int, int>>> wordToRectanglesMap; 

    void processIndices(const std::vector<std::pair<int, int>>& indices, const std::unordered_map<std::string, std::vector<std::pair<int, int>>>& wordToRectanglesMap, std::vector<std::vector<sf::RectangleShape>>& rectangles, int rows, int cols, float rectWidth, float rectHeight, float startX, float startY, float spacing);

    bool isValidWord(const std::string& word);
    bool allWordsFound() const;
    void resetGame();
    void updatePointsText();
    void updateLevelsText();
    void loadLevel1();
    void loadLevel2();
    void loadLevel3();
    void loadLevel4();
    void loadLevel5();
    void nextLevel();
    void clearRectangles();

   
    struct pair_hash {
        template <class T1, class T2>
        std::size_t operator()(const std::pair<T1, T2>& pair) const {
            return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
        }
    };

    std::unordered_set<std::pair<int, int>, pair_hash> validIndices; 
    float rectWidth; 
    float rectHeight; 
    int currentLevel; 
};

#endif