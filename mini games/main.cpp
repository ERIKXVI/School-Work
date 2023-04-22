#include <iostream>
#include <string>
#include "games/hangman.h"


using namespace std;

void mainmenu()
{
	cout << "Welcome to the main menu!" << endl;
	cout << "Please select a game to play:" << endl;
	cout << "1. Hangman" << endl;
	cout << "2. Tic Tac Toe" << endl;
	cout << "3. Blackjack" << endl;
	cout << "4. Snake" << endl;
	cout << "5. Minesweeper" << endl;
	cout << "6. Space Invaders" << endl;
	cout << "7. Pacman" << endl;
	cout << "8. Exit" << endl;
	cout << "Enter your choice: ";
}

int main()
{
    int choice;

    do {
 
        mainmenu();
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            Hangman hangman;
            hangman.play();
            break;
        }
        case 2:
            // Code for Tic Tac Toe game
            break;
        case 3:
            // Code for Blackjack game
            break;
        case 4:
            // Code for Snake game
            break;
        case 5:
            // Code for Minesweeper game
            break;
        case 6:
            // Code for Space Invaders game
            break;
        case 7:
            // Code for Pacman game
            break;
        case 8:
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
            break;
        }
    } while (choice != 8);
    return 0;
}