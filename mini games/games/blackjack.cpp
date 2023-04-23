#include "blackjack.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

using namespace std;

blackjack::blackjack() 
{
    // Initialize the deck
    for (int i = 1; i <= 13; i++)
    {
        for (int j = 0; j < 4; j++) 
        {
            deck.push_back(i);
        }
    }

    // Shuffle the deck
    srand(time(nullptr));
    shuffle(deck.begin(), deck.end(), default_random_engine(rand()));
}

void blackjack::play()
{
    system("cls");

    //deal the initial hands
    player_hand.push_back(deal_card());
    dealer_hand.push_back(deal_card());
    player_hand.push_back(deal_card());
    dealer_hand.push_back(deal_card());

    // print the initial hands
    cout << "Players hand: ";
    print_hand(player_hand, false);
    cout << endl;
    cout << "Dealers hand: ";
    print_hand(dealer_hand, true);
    cout << endl;

    // players turn
    while (true)
    {
        cout << "Hit or stand? (h/s): ";
        string input;
        cin >> input;
        if (input == "h")
        {
            player_hand.push_back(deal_card());
            system("cls");
            cout << "Players hand: ";
            print_hand(player_hand, false);
            cout << endl;

            if (get_score(player_hand) > 21)
            {
                cout << "Bust! You lose." << endl;
                return;
            }
        }
        else
        {
            break;
        }
    }

    // dealers turn
    cout << "Dealers hand: ";
    print_hand(dealer_hand, false);
    cout << endl;
    while (get_score(dealer_hand) < 17)
    {
        dealer_hand.push_back(deal_card());
        system("cls");
        cout << "Dealers hand: ";
        print_hand(dealer_hand, false);
        cout << endl;

        if (get_score(dealer_hand) > 21)
        {
            cout << "Dealer busts! You win." << endl;
            return;
        }
    }

    // determine the winner
    player_score = get_score(player_hand);
    dealer_score = get_score(dealer_hand);
    if (player_score > dealer_score)
    {
        cout << "You win!" << endl;
    }
    else if (player_score < dealer_score)
    {
        cout << "Dealer wins!" << endl;
    }
    else
    {
        cout << "Tie game!" << endl;
    }
}



int blackjack::deal_card()
{
    int card = deck.back();
    deck.pop_back();
    return card;
}

int blackjack::get_score(vector<int>& hand)
{
    int score = 0;
    int num_aces = 0;
    for (int card : hand)
    {
        if (card == 1)
        {
            num_aces++;
            score += 11;
        }
        else if (card > 10)
        {
			score += 10;
		}
        else
        {
			score += card;
        }
    }
    while (num_aces > 0 && score > 21)
    {
        score -= 10;
        num_aces--;
    }
    return score;
}

void blackjack::print_card(int card)
{
    if (card == 1)
    {
        cout << "A";
    }
    else if (card <= 10)
    {
        cout << card;
    }
    else if (card == 11)
    {
        cout << "J";
    }
    else if (card == 12)
    {
        cout << "Q";
    }
    else if (card == 13)
    {
        cout << "K";
    }
}


void blackjack::print_hand(vector<int>& hand, bool hide_first_card)
{
    for (int i = 0; i < hand.size(); i++)
    {
        if (i == 0 && hide_first_card)
        {
            cout << "X ";
        }
        else
        {
			print_card(hand[i]);
			cout << " ";
        }
    }
}