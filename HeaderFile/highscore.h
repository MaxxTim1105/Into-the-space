#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <string>
#include <fstream>
#include <iostream>

class HighScoreManager {
private:
    int highScore;
    std::string filePath;

public:
    HighScoreManager(const std::string& filePath);
    ~HighScoreManager();

    void loadHighScore();
    void saveHighScore();
    void updateHighScore(int score);
    int getHighScore() const;
};

#endif 
