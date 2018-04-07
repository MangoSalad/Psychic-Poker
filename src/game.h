#ifndef GAME_H
#define GAME_H

#include "stdafx.h"

class game
{
public:

    // Default constructor.
    game();

    // Constructor for loading input.
    game(std::vector<std::vector<std::string> > a_input);

    // Shows the input game hands.
    void show_input();

    // Shows output which includes hands and best available hands.
    void show_output();

    // Responsible for strategy thats calculates the best hand for each hand.
    void calculate_best_hand();

private:

    // Tuple holding each card:  <0> rank of card, <1> suit of card, <2> : deck card or original hand card
    typedef std::tuple<char,char,std::string> hand;

    // Iterator for navigating each hand.
    typedef std::vector<hand>::iterator iter;

    // Available choices for best hands.
    const std::string STRAIGHT_FLUSH = "straight-flush";
    const std::string FOUR_OF_A_KIND = "four-of-a-kind";
    const std::string FULL_HOUSE = "full-house";
    const std::string FLUSH = "flush";
    const std::string STRAIGHT = "straight";
    const std::string THREE_OF_A_KIND = "three-of-a-kind";
    const std::string TWO_PAIRS = "two-pairs";
    const std::string ONE_PAIR = "one-pair";
    const std::string HIGHEST_CARD = "highest-card";

    // Hand Card, Deck Card
    const std::string HAND_CARD = "hand";
    const std::string DECK_CARD = "deck";

    // Input 2d matrix.
    std::vector<std::vector<hand> > m_input;
    std::vector<std::string> m_best_hand;
    
    // Checks if a given hand can match the following best hands:
    bool is_straight_flush(std::vector<hand> cards);
    bool is_four_of_a_kind(std::vector<hand> cards);
    bool is_full_house(std::vector<hand> cards);
    bool is_flush(std::vector<hand> cards);
    bool is_straight(std::vector<hand> cards);
    bool is_three_of_a_kind(std::vector<hand> cards);
    bool is_two_pairs(std::vector<hand> cards);
    bool is_one_pair(std::vector<hand> cards);

    // Utility functions. Comprator functions used for sorting.
    static bool compare_rank(const hand &one, const hand &two);
    static bool compare_suit(const hand &one, const hand &two);

    // Checks if rank a < rank b.
    bool is_sequential(const char a, const char b);

    // Checks if the final best available hand is valid. Checks that deck's ordered property is maintained.
    bool is_valid_final_hand(const std::vector<hand> final_hand, std::stack<int> suit_stack, const std::vector<hand> original_cards);
    bool is_valid_final_Hand(std::vector<hand> original_cards, std::stack<hand> final_Cards );
    bool is_valid_sequential_stack(const std::vector<hand> final_hand, std::stack<int> suit_stack);
};

#endif