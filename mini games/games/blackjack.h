#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <vector>

class blackjack {
private:
    std::vector<int> deck;
    std::vector<int> player_hand;
    std::vector<int> dealer_hand;
    int player_score;
    int dealer_score;

    int deal_card();
    int get_score(std::vector<int>& hand);
    void print_card(int card);
    void print_hand(std::vector<int>& hand, bool hide_first_card);

public:
    blackjack();
    void play();
};

#endif // BLACKJACK_H