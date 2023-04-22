#include "hangman.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

Hangman::Hangman() {
    // Read the words from the file
    words = { "umbrella", "laptop", "telephone", "elephant", "mountain", "candle", "skyscraper", "guitar", "sunflower" };

    srand(time(nullptr));

    gueesLeft = 10;
    word = randomWord();
    guessed = "";
    wrong = "";
}

string Hangman::randomWord() {
    int index = rand() % words.size();
    return words[index];
}

void Hangman::play() {

    while (!isGameOver())
    {
        printHangman();
        cout << displayWord() << endl;
        printWrong();
        printGuesses();

        // Get the guess
        char c;
        cout << "Enter your guess: ";
        cin >> c;

        if (isGuessed(c))
        {
            cout << "You already guessed that letter!" << endl;
        }
        else if (isWrong(c))
        {
            cout << "The letter is not in the word!" << endl;
        }
        else
        {
            guessed += c;
            if (word.find(c) == string::npos)
            {
                wrong += c;
                gueesLeft--;
            }
        }

    }

    printGameOver();
}

bool Hangman::isGuessed(char c) {
    return guessed.find(c) != string::npos;
}

bool Hangman::isWrong(char c) {
    return wrong.find(c) != string::npos;
}

bool Hangman::isGameOver()
{
    if (gueesLeft == 0)
    {
        return true;
    }

    for (char c : word)
    {
        if (!isGuessed(c))
        {
            return false;
        }
    }

    return true;
}

string Hangman::displayWord()
{
    string displayed = "";
    for (char c : word)
    {
        if (isGuessed(c))
        {
            displayed += c;
        }
        else
        {
            displayed += "_";
        }
        displayed += " "; // added space to separate the letters
    }
    return displayed;
}

void Hangman::printHangman()
{
    system("cls");
    cout << endl << "  +--+ " << endl;
    cout << "  |    | " << endl;
    cout << "  |    " << (gueesLeft < 10 ? "O" : "") << endl;
    cout << "  |   " << (gueesLeft < 8 ? "/" : " ") << (gueesLeft < 9 ? "|" : "") << (gueesLeft < 7 ? "\\" : "") << endl;
    cout << "  |    " << (gueesLeft < 6 ? "|" : "") << endl;
    cout << "  |   " << (gueesLeft < 5 ? "/" : " ") << " " << (gueesLeft < 6 ? "\\" : "") << endl;
    cout << "  | " << endl;
    cout << "-----" << endl;
}

void Hangman::printWrong()
{
    cout << "Incorrect letters: ";
    for (char c : wrong)
    {
        cout << c << " ";
    }
    cout << endl << endl;
}

void Hangman::printGuesses()
{
   cout << "Guesses left: " << gueesLeft << endl;
}

void Hangman::printGameOver()
{
    cout << endl << "----------------------" << endl;

    cout << "The word was: " << word << endl;

    if (isGameOver() && gueesLeft > 0)
    {
        cout << "Congratulations! You won!" << endl;
    } 
    else
    {
        cout << "Game over! You lost!" << endl;
    }

    cout << "----------------------" << endl;
}