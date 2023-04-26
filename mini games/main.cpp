#include <iostream>
#include <string>
#include "games/hangman.h"
#include "games/tictaktoe.h"
#include "games/blackjack.h"
#include "games/snake.h"
#include "games/minesweeper.h"

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
    bool playAgain;

    do
    {
        playAgain = false;
        mainmenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            Hangman hangman;
            hangman.play();

            // Clear screen after game is finished
            system("cls");

            // Ask if player wants to play again
            char again;
            cout << "Play again? (Y/N): ";
            cin >> again;
            if (tolower(again) == 'y')
            {
                playAgain = true;
            }
            break;
        }
        case 2:
        {
            tictactoe tictactoe;
            tictactoe.play();

            // Clear screen after game is finished
            system("cls");

            // Ask if player wants to play again
            char again;
            cout << "Play again? (Y/N): ";
            cin >> again;
            if (tolower(again) == 'y')
            {
                playAgain = true;
            }
            break;
        }
        case 3:
        {
            blackjack blackjack;
            blackjack.play();

            // Clear screen after game is finished
            system("cls");

            // Ask if player wants to play again
            char again;
            cout << "Play again? (Y/N): ";
            cin >> again;
            if (tolower(again) == 'y')
            {
                playAgain = true;
            }
            break;
        }
        case 4:
        {
            Snake snake(20, 20);
            snake.draw();

            while (!snake.isGameOver())
            {
                char key;
                cin >> key;
                snake.input(key);
                snake.move();
                snake.draw();
            }

            cout << "Game over! Your score was: " << snake.getScore() << endl;

            // Ask if player wants to play again
            char again;
            cout << "Play again? (Y/N): ";
            cin >> again;
            if (tolower(again) == 'y')
            {
                playAgain = true;
            }
            break;
        }

        case 5:
        {
            Minesweeper minesweeper;
            minesweeper.playGame();

            // Clear screen after game is finished
            system("cls");

            // Ask if player wants to play again
            char again;
            cout << "Play again? (Y/N): ";
            cin >> again;
            if (tolower(again) == 'y')
            {
                playAgain = true;
            }
            break;
        }

        case 6:
            cout << "space invaders is not implemented yet!" << endl;
            break;
        case 7:
            cout << "pacman is not implemented yet!" << endl;
            break;
        case 8:
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
            break;
        }

    } while (choice != 8 && playAgain);

    return 0;
}