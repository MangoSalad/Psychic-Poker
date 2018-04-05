#include "game.h"

game::game()
{

};

game::game(std::vector<std::vector<std::string> > a_input)
{
    // Size local variable appropriately.
    m_input.resize(a_input.size());

    // m_hand.resize(a_input.size());
    // m_deck.resize(a_input.size());

    // Assign a_input to m_input.
    for(int i=0; i<a_input.size(); i++)
    {
        m_input[i].resize(a_input.size());

        // m_hand[i].resize(5);
        // m_deck[i].resize(5);
        
        for(int j=0; j<a_input[0].size(); j++)
        {
            m_input[i][j] = a_input[i][j];

            // if(j>=5)
            // {
            //     m_deck[i].push_back(a_input[i][j]);
            // }
            // else
            // {
            //     m_hand[i].push_back(a_input[i][j]);
            // }
        }
    }
};

void game::show_input()
{
    for(int i=0; i<m_input.size(); i++)
    {
        for(int j=0; j<m_input[0].size(); j++)
        {
            std::cout << m_input[i][j] << " ";
        }
        std::cout << std::endl;
    }
};