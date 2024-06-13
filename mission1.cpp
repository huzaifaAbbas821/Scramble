#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <set>
#include <map>
#include <cmath>
#include "mission1.h"

using namespace sf;
using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

vector<string> mission1::validWords = { "TEAM", "NAME", "TAME","MEAN", "MANE", "MEANT", "MATE", "MEAT", "NEAT" };

Color newColor(128, 128, 128);

mission1::mission1() : window(VideoMode(1200, 800), "Scramble Word Game", sf::Style::Close), rectWidth(40.0f), rectHeight(40.0f), points(0), levels(1), showCorrectMessage(false), currentLevel(1) {

    if (!backgroundMusic.openFromFile("assets/music/scrmbmusic.wav")) {
        cerr << "Error loading background music" << endl;
    }
    backgroundMusic.setVolume(50);
    backgroundMusic.setLoop(true); 
    backgroundMusic.play(); 
    if (!font.loadFromFile("assets/fonts/Algerian.ttf")) {
        cerr << "Error loading font\n";
    }

    if (!correctTexture.loadFromFile("assets/images/correct.png")) {
        cerr << "Error loading correct image\n";
    }

    correctSprite.setTexture(correctTexture);
    correctSprite.setPosition(600, 400); 

    levelText.setFont(font);
    levelText.setCharacterSize(40);
    levelText.setFillColor(Color(25, 25, 112));
    levelText.setPosition(550, 10);
    levels = 1;
    updateLevelsText();

    pointsText.setFont(font);
    pointsText.setCharacterSize(40);
    pointsText.setFillColor(Color(25, 25, 112));
    pointsText.setPosition(10, 70);
    updatePointsText();

    messageText.setFont(font);
    messageText.setCharacterSize(60);
    messageText.setFillColor(Color::Magenta);
    messageText.setPosition(220, 220);

    loadLevel5();
}
void mission1::clearRectangles() {
    rectangles.clear();
    validIndices.clear();
    rectangleLetters.clear();
}

void mission1::processIndices(const vector<pair<int, int>>& indices, const unordered_map<string, vector<pair<int, int>>>& wordToRectanglesMap, vector<vector<RectangleShape>>& rectangles, int rows, int cols, float rectWidth, float rectHeight, float startX, float startY, float spacing) {
    for (const auto& index : indices) {
        int row = index.first;
        int col = index.second;

        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            RectangleShape rect(Vector2f(rectWidth, rectHeight));
            rect.setPosition(startX + col * (rectWidth + spacing), startY + row * (rectHeight + spacing));
            rect.setFillColor(Color(128, 128, 128));
            rectangles[row][col] = rect;
        }
    }

    // Additional logic to associate letters with specific rectangles based on words
    rectangleLetters.clear();
    for (const auto& wordEntry : wordToRectanglesMap) {
        const string& word = wordEntry.first;
        const auto& wordIndices = wordEntry.second;

        for (size_t i = 0; i < wordIndices.size(); ++i) {
            int row = wordIndices[i].first;
            int col = wordIndices[i].second;
            if (row >= 0 && row < rows && col >= 0 && col < cols) {
                Text letterText(word.substr(i, 1), font, 30);
                letterText.setFillColor(newColor);
                letterText.setPosition(startX + col * (rectWidth + spacing) + rectWidth / 2 - 10, startY + row * (rectHeight + spacing) + rectHeight / 2 - 15);
                rectangleLetters.push_back(letterText);
            }
        }
    }
}

void mission1::loadLevel1() {
    clearRectangles();
    if (!backgroundTexture.loadFromFile("assets/images/mk.png")) {
        cerr << "Error loading background image\n";
    }
    backgroundTexture.setSmooth(true);
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

    
    points = 0;
    updatePointsText();

    
    string letters = "TMANE";
    size_t numLetters = letters.size();
    float radius = max(85.0f, numLetters * 16.0f);
    Vector2f center(window.getSize().x / 2.0f, window.getSize().y * 0.8f);

    
    mainCircle.setRadius(110);
    
    mainCircle.setFillColor(Color(0, 0, 128)); 
    mainCircle.setPosition(490.0f, window.getSize().y * 0.68f);

    letterCircles.clear();
    givenLetters.clear();
    for (size_t i = 0; i < numLetters; ++i) {
        float angle = (i * 72.0f) * (M_PI / 180.0f); 
        Vector2f position(center.x + radius * cos(angle), center.y + radius * sin(angle));

        CircleShape circle(30.0f);
        circle.setFillColor(Color(255, 255, 255, 0));
        circle.setPosition(position.x - circle.getRadius(), position.y - circle.getRadius());
        letterCircles.push_back(circle);

        Text letter(letters.substr(i, 1), font, 35);
        letter.setFillColor(Color::White);
        FloatRect textBounds = letter.getLocalBounds();
        letter.setOrigin(textBounds.width / 2.0f, textBounds.height / 2.0f);
        letter.setPosition(position.x, position.y);
        givenLetters.push_back(letter);
    }

   
    wordTexts.clear();
    for (int i = 0; i < numLetters; ++i) {
        Text wordText("", font, 60);
        wordText.setFillColor(Color::White);
        wordText.setPosition(600.0f, 490.0f);
        wordTexts.push_back(wordText);
    }

   
    int rows = 7;
    int cols = 9;
    float startX = 400.0f; 
    float startY = 90.0f; 
    float spacing = 3.0f; 

    rectangles.resize(rows, vector<RectangleShape>(cols));

   
    validIndices = {
        {0, 6}, {1, 0}, {1, 4},{1, 5}, {1, 6}, {1, 7}, {2, 0}, {2, 2},
        {2, 6}, {3, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 5}, {3, 6}, {3, 7},
        {3, 8}, {4, 0}, {4, 2}, {4, 5}, {4, 8}, {5, 1}, {5, 2}, {5, 3},
        {5, 4}, {5, 5}, {5, 8}, {6, 5}, {6, 8}
    };

  
    wordToRectanglesMap.clear();
    wordToRectanglesMap["TAME"] = { {1, 0}, {2, 0}, {3, 0}, {4, 0} };
    wordToRectanglesMap["TEAM"] = { {3, 8}, {4, 8}, {5, 8}, {6, 8} };
    wordToRectanglesMap["MEAN"] = { {3, 0}, {3, 1}, {3, 2}, {3, 3} };
    wordToRectanglesMap["MANE"] = { {2, 2}, {3, 2}, {4, 2}, {5, 2} };
    wordToRectanglesMap["MEANT"] = { {5, 1}, {5, 2}, {5, 3}, {5, 4}, {5, 5} };
    wordToRectanglesMap["MEAT"] = { {3, 5}, {3, 6}, {3, 7}, {3, 8} };
    wordToRectanglesMap["NEAT"] = { {1, 4}, {1, 5}, {1, 6}, {1, 7} };
    wordToRectanglesMap["NAME"] = { {3, 6}, {2, 6}, {1, 6}, {0, 6} };

    std::vector<std::pair<int, int>> validIndicesVec(validIndices.begin(), validIndices.end());

    newColor = Color(128, 128, 128);

    processIndices(validIndicesVec, wordToRectanglesMap, rectangles, rows, cols, 40.0f, 40.0f, startX, startY, spacing);
}

void mission1::loadLevel2() {
    levels = 2;
    currentLevel = levels;
    pointsText.setFillColor(Color::White);
    levelText.setFillColor(Color::White);
    updateLevelsText();
    clearRectangles();
    if (!backgroundTexture.loadFromFile("assets/images/ntu.png")) {
        cerr << "Error loading background image for level 2\n";
    }
    backgroundTexture.setSmooth(true);
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

   
    points = 0;
    updatePointsText();

   
    string letters = "NESTT"; 
    size_t numLetters = letters.size();
    float radius = max(85.0f, numLetters * 16.0f);
    Vector2f center(window.getSize().x / 2.0f, window.getSize().y * 0.8f); 

   
    mainCircle.setRadius(110);
    mainCircle.setFillColor(Color(50, 205, 50)); 
    mainCircle.setPosition(490.0f, window.getSize().y * 0.68f);

    letterCircles.clear();
    givenLetters.clear();
    int numCircles = letters.size();
    float angleStep = 360.0f / numCircles;
    float smallCircleRadius = 70.0f;
    
    for (int i = 0; i < numCircles; ++i) {
        float angle = i * angleStep * (M_PI / 180.0f);
        float circleX = center.x + smallCircleRadius * cos(angle);
        float circleY = center.y + smallCircleRadius * sin(angle);

        CircleShape smallCircle(30.0f);
        smallCircle.setFillColor(Color(255, 255, 255, 0));
        smallCircle.setPosition(circleX - smallCircle.getRadius(), circleY - smallCircle.getRadius());
        letterCircles.push_back(smallCircle);

        Text letterText;
        letterText.setFont(font);
        letterText.setString(letters[i]);
        letterText.setCharacterSize(35);
        letterText.setFillColor(Color::White);
        FloatRect textBounds = letterText.getLocalBounds();
        letterText.setOrigin(textBounds.width / 2.0f, textBounds.height / 2.0f);
        letterText.setPosition(circleX, circleY);
        givenLetters.push_back(letterText);
    }
    vector<string> validWordsLevel2 = { "NET", "NEST", "TEN", "SENT", "TENT", "STENT" };
    validWords = validWordsLevel2;

   
    wordTexts.clear();
    for (int i = 0; i < numLetters; ++i) {
        Text wordText("", font, 60);
        wordText.setFillColor(Color::White);
        wordText.setPosition(600.0f, 490.0f);
        wordTexts.push_back(wordText);
    }

    
    int rows = 6;
    int cols = 9;
    float startX = 475.0f;
    float startY = 90.0f; 
    float spacing = 5.0f; 

    rectangles.resize(rows, vector<RectangleShape>(cols));

    
    validIndices = {
        {1,0},{2,0},{3,0} ,
        {1,0},{1,1},{1,2},{1,3},
        {3,0},{3,1},{3,2},
        {1,2},{2,2},{3,2},{4,2},
        {4,2},{4,3},{4,4},{4,5},
        {0,5},{1,5},{2,5},{3,5 },{ 4,5 }
    };
   
    wordToRectanglesMap.clear();
    wordToRectanglesMap["NET"] = { {1,0},{2,0},{3,0} };
    wordToRectanglesMap["NEST"] = { {1,0},{1,1},{1,2},{1,3} };
    wordToRectanglesMap["TEN"] = { {3,0},{3,1},{3,2 } };
    wordToRectanglesMap["SENT"] = { {1,2},{2,2},{3,2},{4,2 } };
    wordToRectanglesMap["TENT"] = { {4,2},{4,3},{4,4},{4,5} };
    wordToRectanglesMap["STENT"] = { {0,5},{1,5},{2,5},{3,5 },{ 4,5 } };

    vector<pair<int, int>> validIndicesVec(validIndices.begin(), validIndices.end());

    processIndices(validIndicesVec, wordToRectanglesMap, rectangles, rows, cols, 50.0f, 50.0f, startX, startY, spacing);
}

void mission1::loadLevel3() {
    levels = 3;
    currentLevel = levels;
    pointsText.setFillColor(Color::White);
    levelText.setFillColor(Color::White);
    updateLevelsText();
    clearRectangles();
    if (!backgroundTexture.loadFromFile("assets/images/mission1.png")) {
        cerr << "Error loading background image for level 2\n";
    }
    backgroundTexture.setSmooth(true);
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

    
    points = 0;
    updatePointsText();

    vector<string> validWordsLevel3 = { "COLA","FALCON" , "CONF","FOCAL" , "CALF" ,"COAL" ,"CLON","FAN" ,"LOAN" };
    validWords = validWordsLevel3;

    
    string letters = "CONLFA"; 
    size_t numLetters = letters.size();
    float radius = max(85.0f, numLetters * 16.0f);
    Vector2f center(window.getSize().x / 2.0f, window.getSize().y * 0.8f); 

    
    mainCircle.setRadius(110);
    mainCircle.setFillColor(Color(25, 25, 112)); 
    mainCircle.setPosition(490.0f, window.getSize().y * 0.68f);

    letterCircles.clear();
    givenLetters.clear();
    int numCircles = letters.size();
    float angleStep = 360.0f / numCircles;
    float smallCircleRadius = 60.0f;
   
    for (int i = 0; i < numCircles; ++i) {
        float angle = i * angleStep * (M_PI / 180.0f);
        float circleX = center.x + smallCircleRadius * cos(angle);
        float circleY = center.y + smallCircleRadius * sin(angle);

        CircleShape smallCircle(30.0f);
        smallCircle.setFillColor(Color(255, 255, 255, 0));
        smallCircle.setPosition(circleX - smallCircle.getRadius(), circleY - smallCircle.getRadius());
        letterCircles.push_back(smallCircle);

        Text letterText;
        letterText.setFont(font);
        letterText.setString(letters[i]);
        letterText.setCharacterSize(35);
        letterText.setFillColor(Color::White);
        FloatRect textBounds = letterText.getLocalBounds();
        letterText.setOrigin(textBounds.width / 2.0f, textBounds.height / 2.0f);
        letterText.setPosition(circleX, circleY);
        givenLetters.push_back(letterText);
    }

   
    wordTexts.clear();
    for (int i = 0; i < numLetters; ++i) {
        Text wordText("", font, 60);
        wordText.setFillColor(Color::White);
        wordText.setPosition(600.0f, 490.0f);
        wordTexts.push_back(wordText);
    }

   
    int rows = 6;
    int cols = 9;
    float startX = 400.0f; 
    float startY = 100.0f; 
    float spacing = 5.0f; 

    rectangles.resize(rows, vector<RectangleShape>(cols));

    
    validIndices = {
        {1,0},{1,1},{1,2},{1,3},
        {0,3},{1,3},{2,3},{3,3},{4,3},{5,3},{6,3},
        {0,1},{1,1,},{2,1},{3,1},
        {3,1},{3,2},{3,3},{3,4},{3,5},
        {1,5},{2,5},{3,5},{4,5},
        {1,5},{1,6},{1,7},{1,8},
        {0,8},{1,8},{2,8},{3,8},
        {4,5},{4,6},{4,7},
        {5,0} ,{5,1},{5,2},{5,3},
    };
    
    wordToRectanglesMap.clear();
    wordToRectanglesMap["COLA"] = { {1,0},{1,1},{1,2},{1,3}, };
    wordToRectanglesMap["FALCON"] = { {0,3},{1,3},{2,3},{3,3},{4,3},{5,3} };
    wordToRectanglesMap["CONF"] = { {0,1},{1,1,},{2,1},{3,1}, };
    wordToRectanglesMap["FOCAL"] = { {3,1},{3,2},{3,3},{3,4},{3,5}, };
    wordToRectanglesMap["CALF"] = { {1,5},{2,5},{3,5},{4,5}, };
    wordToRectanglesMap["COAL"] = { {1,5},{1,6},{1,7},{1,8}, };
    wordToRectanglesMap["CLON"] = { {0,8},{1,8},{2,8},{3,8} };
    wordToRectanglesMap["FAN"] = { {4,5},{4,6},{4,7} };
    wordToRectanglesMap["LOAN"] = { {5,0} ,{5,1},{5,2},{5,3} };

    std::vector<std::pair<int, int>> validIndicesVec(validIndices.begin(), validIndices.end());

    processIndices(validIndicesVec, wordToRectanglesMap, rectangles, rows, cols, 40.0f, 40.0f, startX, startY, spacing);
}

void mission1::loadLevel4() {
    levels = 4;
    currentLevel = levels;
    pointsText.setFillColor(Color(105, 105, 105));
    levelText.setFillColor(Color(105, 105, 105));
    updateLevelsText();
    clearRectangles();
    if (!backgroundTexture.loadFromFile("assets/images/brown.png")) {
        cerr << "Error loading background image for level 2\n";
    }
    backgroundTexture.setSmooth(true);
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

   
    points = 0;
    updatePointsText();

    vector<string> validWordsLevel4 = { "COAT" , "ACTOR" , "CARROT" , "OAT" , "CART" , "TACO" , "COT" , "TOC" ,"ACT" };
    validWords = validWordsLevel4;

   
    string letters = "ACTORR"; 
    size_t numLetters = letters.size();
    float radius = max(85.0f, numLetters * 16.0f);
    Vector2f center(window.getSize().x / 2.0f, window.getSize().y * 0.8f); 

   
    mainCircle.setRadius(110);
    mainCircle.setFillColor(Color(139, 69, 19)); 
    mainCircle.setPosition(490.0f, window.getSize().y * 0.68f);

    letterCircles.clear();
    givenLetters.clear();
    int numCircles = letters.size();
    float angleStep = 360.0f / numCircles;
    float smallCircleRadius = 70.0f; 
   
    for (int i = 0; i < numCircles; ++i) {
        float angle = i * angleStep * (M_PI / 180.0f);
        float circleX = center.x + smallCircleRadius * cos(angle);
        float circleY = center.y + smallCircleRadius * sin(angle);

        CircleShape smallCircle(30.0f);
        smallCircle.setFillColor(Color(255, 255, 255, 0));
        smallCircle.setPosition(circleX - smallCircle.getRadius(), circleY - smallCircle.getRadius());
        letterCircles.push_back(smallCircle);

        Text letterText;
        letterText.setFont(font);
        letterText.setString(letters[i]);
        letterText.setCharacterSize(35);
        letterText.setFillColor(Color::White);
        FloatRect textBounds = letterText.getLocalBounds();
        letterText.setOrigin(textBounds.width / 2.0f, textBounds.height / 2.0f);
        letterText.setPosition(circleX, circleY);
        givenLetters.push_back(letterText);
    }

   
    wordTexts.clear();
    for (int i = 0; i < numLetters; ++i) {
        Text wordText("", font, 60);
        wordText.setFillColor(Color::White);
        wordText.setPosition(600.0f, 490.0f);
        wordTexts.push_back(wordText);
    }

    
    int rows = 7;
    int cols = 9;
    float startX = 400.0f; 
    float startY = 70.0f; 
    float spacing = 5.0f; 

    rectangles.resize(rows, vector<RectangleShape>(cols));

   
    validIndices = {
                {5,0,},{5,1},{5,2},{5,3},
                {2,1},{3,1},{4,1},{5,1},{6,1},
                {3,1},{3,2},{3,3},{3,4},{3,5},{3,6},
                {3,5},{4,5},{5,5},
                {0,6},{1,6},{2,6},{3,6},
                {1,5},{1,6},{1,7},{1,8},
                {0,8},{1,8},{2,8},
                {5,5},{5,6},{5,7},
                {4,7},{5,7},{6,7},
    };
   
    wordToRectanglesMap.clear();    wordToRectanglesMap["COLA"] = { {1,0},{1,1},{1,2},{1,3}, };
    wordToRectanglesMap["COAT"] = { {5,0,},{5,1},{5,2},{5,3}, };
    wordToRectanglesMap["ACTOR"] = { {2,1},{3,1},{4,1},{5,1},{6,1}, };
    wordToRectanglesMap["CARROT"] = { {3,1},{3,2},{3,3},{3,4},{3,5},{3,6}, };
    wordToRectanglesMap["OAT"] = { {3,5},{4,5},{5,5}, };
    wordToRectanglesMap["CART"] = { {0,6},{1,6},{2,6},{3,6}, };
    wordToRectanglesMap["COT"] = { {0,8},{1,8},{2,8} };
    wordToRectanglesMap["TACO"] = { {1,5},{1,6},{1,7},{1,8} };
    wordToRectanglesMap["TOC"] = { {5,5},{5,6},{5,7} };
    wordToRectanglesMap["ACT"] = { {4,7},{5,7},{6,7} };

    std::vector<std::pair<int, int>> validIndicesVec(validIndices.begin(), validIndices.end());

    processIndices(validIndicesVec, wordToRectanglesMap, rectangles, rows, cols, 40.0f, 40.0f, startX, startY, spacing);
}

void mission1::loadLevel5() {
    levels = 5;
    currentLevel = levels;
    pointsText.setFillColor(Color::Black);
    levelText.setFillColor(Color::Black);
    updateLevelsText();
    clearRectangles();
    if (!backgroundTexture.loadFromFile("assets/images/level5.png")) {
        cerr << "Error loading background image for level 2\n";
    }
    backgroundTexture.setSmooth(true);
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

   
    points = 0;
    updatePointsText();

    vector<string> validWordsLevel5 = { "MOST" , "SHOOT" , "SHOT" , "SMOOTH" , "HOOT" , "HOT" , "HOST" };
    validWords = validWordsLevel5;

    
    string letters = "SHTOOM"; 
    size_t numLetters = letters.size();
    float radius = max(85.0f, numLetters * 16.0f);
    Vector2f center(window.getSize().x / 2.0f, window.getSize().y * 0.8f); 

    
    mainCircle.setRadius(110);
    mainCircle.setFillColor(Color(139, 69, 19)); 
    mainCircle.setPosition(490.0f, window.getSize().y * 0.68f);

    letterCircles.clear();
    givenLetters.clear();
    int numCircles = letters.size();
    float angleStep = 360.0f / numCircles;
    float smallCircleRadius = 65.0f; 
   
    for (int i = 0; i < numCircles; ++i) {
        float angle = i * angleStep * (M_PI / 180.0f);
        float circleX = center.x + smallCircleRadius * cos(angle);
        float circleY = center.y + smallCircleRadius * sin(angle);

        CircleShape smallCircle(30.0f);
        smallCircle.setFillColor(Color(255, 255, 255, 0));
        smallCircle.setPosition(circleX - smallCircle.getRadius(), circleY - smallCircle.getRadius());
        letterCircles.push_back(smallCircle);

        Text letterText;
        letterText.setFont(font);
        letterText.setString(letters[i]);
        letterText.setCharacterSize(35);
        letterText.setFillColor(Color::White);
        FloatRect textBounds = letterText.getLocalBounds();
        letterText.setOrigin(textBounds.width / 2.0f, textBounds.height / 2.0f);
        letterText.setPosition(circleX, circleY);
        givenLetters.push_back(letterText);
    }

   
    wordTexts.clear();
    for (int i = 0; i < numLetters; ++i) {
        Text wordText("", font, 60);
        wordText.setFillColor(Color::White);
        wordText.setPosition(600.0f, 490.0f);
        wordTexts.push_back(wordText);
    }

   
    int rows = 6;
    int cols = 7;
    float startX = 450.0f; 
    float startY = 100.0f; 
    float spacing = 5.0f; 

    rectangles.resize(rows, vector<RectangleShape>(cols));

   
    validIndices = {
                {1,0,},{2,0},{3,0},{4,0},
               {3,0},{3,1},{3,2},{3,3},{3,4},
               {5,1},{5,2},{5,3},{5,4},
                {0,2},{1,2},{2,2},{3,2} , {4,2} ,{5,2},
                {0,4},{1,4},{2,4},{3,4},
                {0,4},{0,5},{0,6},
                {2,6},{3,6},{4,6},{5,6}
    };
    
    wordToRectanglesMap.clear();    wordToRectanglesMap["COLA"] = { {1,0},{1,1},{1,2},{1,3}, };
    wordToRectanglesMap["MOST"] = { {1,0,},{2,0},{3,0},{4,0}, };
    wordToRectanglesMap["SHOOT"] = { {3,0},{3,1},{3,2},{3,3},{3,4}, };
    wordToRectanglesMap["SHOT"] = { {5,1},{5,2},{5,3},{5,4} };
    wordToRectanglesMap["SMOOTH"] = { {0,2},{1,2},{2,2},{3,2} , {4,2} ,{5,2} };
    wordToRectanglesMap["HOOT"] = { {0,4},{1,4},{2,4},{3,4}, };
    wordToRectanglesMap["HOT"] = { {0,4},{0,5},{0,6} };
    wordToRectanglesMap["HOST"] = { {2,6},{3,6},{4,6},{5,6} };


    std::vector<std::pair<int, int>> validIndicesVec(validIndices.begin(), validIndices.end());

    processIndices(validIndicesVec, wordToRectanglesMap, rectangles, rows, cols, 40.0f, 40.0f, startX, startY, spacing);
}


void mission1::nextLevel() {
    if (currentLevel == 1) {
        loadLevel2();
        currentLevel = 2;
    }
    else if (currentLevel == 2) {
        loadLevel3();
        currentLevel = 3;
    }
    else if (currentLevel == 3) {
        loadLevel4();
        currentLevel = 4;
    }
    else if (currentLevel == 4) {
        loadLevel5();
        currentLevel = 5;
    }

}

bool mission1::isValidWord(const string& word) {
    return find(validWords.begin(), validWords.end(), word) != validWords.end();
}

bool mission1::allWordsFound() const {

    return correctWords.size() == validWords.size();
}

void mission1::updatePointsText() {
    pointsText.setString("Points: " + to_string(points));
}
void mission1::updateLevelsText() {
    levelText.setString("LEVEL: " + to_string(levels));
}

void mission1::resetGame() {
    clickedLetters.clear();
    correctWords.clear();
    showCorrectMessage = false;
    endGame = false;
    points = 0;
    updatePointsText();
    if (currentLevel == 1) {
        loadLevel1();
    }
    else if (currentLevel == 2) {
        loadLevel2();
    }
}

void mission1::run() {
    Clock clock;
    Clock messageClock;
    bool resetPending = false;
    vector<Text> rectangleLetters; 

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {

                backgroundMusic.stop();

                window.close();
            }

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
               

                window.close();
            }

            if (!endGame && event.type == Event::MouseButtonPressed) {
                for (size_t i = 0; i < letterCircles.size(); ++i) {
                    if (letterCircles[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        clickedLetters.push_back(givenLetters[i].getString());
                        break;
                    }
                }
            }

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
                string currentWord;
                for (const auto& letter : clickedLetters) {
                    currentWord += letter;
                }

                if (!currentWord.empty()) {
                    if (isValidWord(currentWord) && find(correctWords.begin(), correctWords.end(), currentWord) == correctWords.end()) {
                        correctWords.push_back(currentWord);
                        showCorrectMessage = true;
                        messageClock.restart(); 
                        points += 10; 
                        updatePointsText();
                        cout << "Correct word: " << currentWord << endl;

                        vector<pair<int, int>> positions = wordToRectanglesMap[currentWord];
                        for (size_t i = 0; i < positions.size(); ++i) {
                            int row = positions[i].first;
                            int col = positions[i].second;
                            rectangles[row][col].setFillColor(Color(65, 105, 225));

                            Text letter(currentWord.substr(i, 1), font, 15);
                            letter.setFillColor(Color::White);
                            FloatRect textBounds = letter.getLocalBounds();
                            letter.setOrigin(textBounds.width / 2.0f, textBounds.height / 2.0f);
                            letter.setPosition(rectangles[row][col].getPosition().x + rectWidth / 2,
                                rectangles[row][col].getPosition().y + rectHeight / 2);
                            rectangleLetters.push_back(letter); 
                        }
                    }
                    else {
                        showCorrectMessage = false;
                    }
                    clickedLetters.clear();
                }
            }
        }

        window.clear();
        window.draw(backgroundSprite);
        window.draw(mainCircle);


       
        for (const auto& circle : letterCircles) {
            window.draw(circle);
        }

        
        for (const auto& letter : givenLetters) {
            window.draw(letter);
        }

        
        for (const auto& row : rectangles) {
            for (const auto& rect : row) {
                window.draw(rect);
            }
        }

       
        for (const auto& letter : rectangleLetters) {
            window.draw(letter);
        }

        
        float clickedLetterX = 500.0f;
        float clickedLetterY = 470.0f;
        for (const auto& letter : clickedLetters) {
            Text clickedLetter(letter, font, 35);
            clickedLetter.setFillColor(Color::Yellow);
            clickedLetter.setPosition(clickedLetterX, clickedLetterY);
            window.draw(clickedLetter);
            clickedLetterX += 40.0f;
        }

       
        for (const auto& wordText : wordTexts) {
            window.draw(wordText);
        }

       
        window.draw(pointsText);
        window.draw(levelText);
       
        if (showCorrectMessage && messageClock.getElapsedTime().asSeconds() < 2.0f) {
            window.draw(correctSprite);
        }
        else {
            showCorrectMessage = false; 
        }

        window.display();

        if (allWordsFound() && !resetPending) {
            
            for (const auto& word : correctWords) {
                if (wordToRectanglesMap.find(word) != wordToRectanglesMap.end()) {
                    const auto& positions = wordToRectanglesMap[word];
                    for (size_t i = 0; i < positions.size(); ++i) {
                        int row = positions[i].first;
                        int col = positions[i].second;
                        rectangles[row][col].setFillColor(Color::Blue);

                        Text letter(word.substr(i, 1), font, 15);
                        letter.setFillColor(Color::White);
                        FloatRect textBounds = letter.getLocalBounds();
                        letter.setOrigin(textBounds.width / 2.0f, textBounds.height / 2.0f);
                        letter.setPosition(rectangles[row][col].getPosition().x + rectWidth / 2,
                            rectangles[row][col].getPosition().y + rectHeight / 2);
                        rectangleLetters.push_back(letter); 
                    }
                }
            }

            resetPending = true;
            clock.restart();
        }

        if (resetPending && clock.getElapsedTime().asSeconds() >= 2.0f) {
            nextLevel();
            resetPending = false;

          
            clickedLetters.clear();
            correctWords.clear();
            rectangleLetters.clear();

        }
    }
}