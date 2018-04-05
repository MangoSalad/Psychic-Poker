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



private:

    std::vector<std::vector<std::string> > m_input;
    
    // Player hands.
    std::vector<std::vector<std::string> >m_hand;

    // Player deck.
    std::vector<std::vector<std::string> > m_deck;
    //recommendations


    

};

#endif