//#ifndef WORDGAME_H
//#define WORDGAME_H
//
//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
//#include <vector>
//#include <string>
//#include <set>
//#include <unordered_set>
//#include <utility>
//
//class WordGame {
//public:
//    WordGame();
//    void run();
//
//private:
//    sf::RenderWindow window;
//    sf::Texture backgroundTexture;
//    sf::Sprite backgroundSprite;
//    sf::Font font;
//    sf::Music music;
//
//    std::vector<sf::CircleShape> letterCircles;
//    std::vector<sf::Text> givenLetters;
//    std::vector<sf::Text> wordTexts;
//    std::vector<sf::RectangleShape> rectangles;
//    std::unordered_set<std::pair<int, int>, pair_hash> greenRectanglesIndices;
//
//    sf::Texture correctTexture;
//    sf::Sprite correctSprite;
//
//    sf::Text messageText;
//
//    std::set<std::string> foundWords;
//    std::vector<std::string> clickedLetters;
//
//    bool showCorrectMessage;
//    bool endGame;
//    bool levelCompleted;
//    int points;
//    float correctMessageDuration;
//    sf::Clock correctMessageClock;
//
//    static std::vector<std::string> validWords;
//
//    void initializeRectangles();
//    void updatePointsText();
//    bool isValidWord(const std::string& word);
//    bool allWordsFound() const;
//
//    struct pair_hash {
//        template <class T1, class T2>
//        std::size_t operator()(const std::pair<T1, T2>& pair) const {
//            return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
//        }
//    };
//};
//
//#endif // WORDGAME_H
