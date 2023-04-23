#ifndef HANGMAN_H
#define HANGMAN_H

#include <vector>
#include <string>

class Hangman {
public:
    Hangman();
    void play();
private:
    std::vector<std::string> words;
    std::string randomWord();
    int gueesLeft;
    std::string word;
    std::string guessed;
    std::string wrong;
    std::string displayWord();
    bool isGuessed(char c);
    bool isWrong(char c);
    bool isGameOver();
    void printHangman();
    void printWord();
    void printWrong();
    void printGuesses();
    void printGameOver();
};

#endif