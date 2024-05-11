#include "highscore.h"

HighScoreManager::HighScoreManager(const std::string& filePath) : filePath(filePath), highScore(0) {
    loadHighScore();
}

HighScoreManager::~HighScoreManager() {
    saveHighScore();
}

void HighScoreManager::loadHighScore() {
    std::ifstream file(filePath);
    if (file.is_open()) {
        file >> highScore;
        file.close();
    }
}

void HighScoreManager::saveHighScore() {
    std::ofstream file(filePath);
    if (file.is_open()) {
        file << highScore;
        file.close();
    }
}

void HighScoreManager::updateHighScore(int score) {
    if (score > highScore) {
        highScore = score;
        saveHighScore();
    }
}

int HighScoreManager::getHighScore() const {
    return highScore;
}
