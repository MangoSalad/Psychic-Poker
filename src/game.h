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

    //debugging functions
    void show_input();

    void show_output();

    // Main strategy for calculating the best hand for each hand.
    void calculate_best_hand();

private:

    // <0> : rank
    // <1> : suit
    // <2> : deck card or hand card
    typedef std::tuple<char,char,std::string> hand;

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

    std::vector<std::vector<hand> > m_input;

    std::vector<std::string> m_best_hand;
    
    // Player hands.
    std::vector<std::vector<std::string> >m_hand;

    // Player deck.
    std::vector<std::vector<std::string> > m_deck;
    
    // Checks if hand is straight flush.
    bool is_straight_flush(const std::vector<hand> cards);

    bool is_four_of_a_kind(const std::vector<hand> cards);

    bool is_full_house(const std::vector<hand> cards);
    
    bool is_flush(const std::vector<hand> cards);

    bool is_straight(const std::vector<hand> cards);

    bool is_three_of_a_kind(const std::vector<hand> cards);

    bool is_two_pairs(const std::vector<hand> cards);

    bool is_one_pair(const std::vector<hand> cards);

    // Utility functions.
    static bool compare_rank(const hand &one, const hand &two);

    bool is_sequential(const char a, const char b);

    bool is_valid_final_hand(const std::vector<hand> final_hand, std::stack<int> suit_stack);
};

#endif