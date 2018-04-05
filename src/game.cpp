#include "game.h"

game::game()
{

};

game::game(std::vector<std::vector<std::string> > a_input)
{
    // Size local variable appropriately.
    m_input.resize(a_input.size());

    // Assign a_input to m_input.
    for(int i=0; i<a_input.size(); i++)
    {
        m_input[i].resize(a_input.size());
        
        for(int j=0; j<a_input[0].size(); j++)
        {
            if(j>5)
            {
                m_input[i][j] = std::make_tuple(a_input[i][j][0],a_input[i][j][1],HAND_CARD);
            }
            else
            {
                m_input[i][j] = std::make_tuple(a_input[i][j][0],a_input[i][j][1],DECK_CARD);
            }
        }
    }
};

void game::show_input()
{
    for(int i=0; i<m_input.size(); i++)
    {
        for(int j=0; j<m_input[0].size(); j++)
        {
            std::cout << std::get<0>(m_input[i][j]) << std::get<1>(m_input[i][j]) << " ";
        }
        std::cout << std::endl;
    }
};

void game::show_output()
{
    for(int i=0; i<m_input.size(); i++)
    {
        for(int j=0; j<m_input[0].size(); j++)
        {
            std::cout << std::get<0>(m_input[i][j]) << std::get<1>(m_input[i][j]) << " ";
        }
        std::cout << m_best_hand[i] << std::endl;
    }
};


void game::calculate_best_hand()
{
    m_best_hand.resize(m_input.size());

    // Cycle through each hand in input.
    for(int i = 0; i < m_input.size(); i++)
    { 
        if(is_straight_flush(m_input[i]))
        {
            m_best_hand[i]=STRAIGHT_FLUSH;
        }
        else
        {
            m_best_hand[i]=HIGHEST_CARD;
        }
    }
}

bool game::is_straight_flush(std::vector<hand> cards)
{
    // Iterators for going through hand and deck cards.
    std::vector<hand>::iterator hand_ptr = cards.begin();
    std::vector<hand>::iterator deck_ptr = cards.begin()+5;

    // Number of sequential cards.
    int num_sequential;

    // Stacks for each suit.
    std::stack<int> count_heart;
    std::stack<int> count_diamond;
    std::stack<int> count_club;
    std::stack<int> count_spade;

    // Iterate through entire hand and deck.
    while(deck_ptr != cards.end()+1)
    {
        num_sequential = 1;

        // Sort cards in sequential order.
        std::sort(cards.begin(),deck_ptr,compare_rank);

        if(std::get<1>(cards[0]) == 'H') count_heart.push(0);
        else if(std::get<1>(cards[0]) == 'D') count_diamond.push(0);
        else if(std::get<1>(cards[0]) == 'C') count_club.push(0);
        else if(std::get<1>(cards[0]) == 'S') count_spade.push(0);

        // Check for sequential rank property and same suit.
        for(int  i = 1; i <= std::distance(cards.begin(),deck_ptr); i++)
        {
            if(num_sequential==5 && (count_heart.size() == 5 || count_diamond.size()  == 5 || count_club.size()  == 5 || count_spade.size()  == 5))
            {
                // Check that ordered deck property is maintained.
                // Cards from original hand + cards from deck = 5.             
                if(count_heart.size()==5)
                {
                    if(is_valid_final_hand(cards,count_heart)) return true;
                }
                else if(count_diamond.size()==5)
                {
                    if(is_valid_final_hand(cards,count_diamond)) return true;
                }
                else if(count_club.size()==5)
                {
                    if(is_valid_final_hand(cards,count_club)) return true;
                }
                else if(count_spade.size()==5)
                {
                    if(is_valid_final_hand(cards,count_spade)) return true;
                } 
            }
            // Skip duplicate rank.
            if(std::get<0>(cards[i-1]) == std::get<0>(cards[i]))
            {
                if(std::get<1>(cards[i])  == 'H') count_heart.push(i);
                else if(std::get<1>(cards[i])=='D') count_diamond.push(i);
                else if(std::get<1>(cards[i])=='C') count_club.push(i);
                else if(std::get<1>(cards[i])=='S') count_spade.push(i);
                continue;
            }
            
            else if(is_sequential(std::get<0>(cards[i-1]),std::get<0>(cards[i]))) //&& cards[i].second == cards[i+1].second)
            {
                if(std::get<1>(cards[i])  == 'H') count_heart.push(i);
                else if(std::get<1>(cards[i])=='D') count_diamond.push(i);
                else if(std::get<1>(cards[i])=='C') count_club.push(i);
                else if(std::get<1>(cards[i])=='S') count_spade.push(i);

                num_sequential++;
            }
            else
            {
                num_sequential=1;
            }
        }

        // Empty the stacks.
        while(!count_heart.empty()) count_heart.pop();
        while(!count_diamond.empty()) count_diamond.pop();
        while(!count_club.empty()) count_club.pop();
        while(!count_spade.empty()) count_spade.pop();

        deck_ptr++;
    }
    
    return false;
}

bool game::is_valid_final_hand(const std::vector<hand> final_hand, std::stack<int> suit_stack)
{
    int cards_from_hand = 0;
    int cards_from_deck = 0;

    while(!suit_stack.empty())
    {
        if(std::get<2>(final_hand[suit_stack.top()]) == HAND_CARD)
        {
            cards_from_hand++;
        }
        else if(std::get<2>(final_hand[suit_stack.top()]) == DECK_CARD)
        {
            cards_from_deck++;
        }
        suit_stack.pop();
    }
    if(cards_from_hand+cards_from_deck==5)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool game::is_sequential(const char a, const char b)
{
    if(a=='A') return false;
    else if(a=='K' && b=='A') return true;
    else if(a=='Q' && b=='K') return true;
    else if(a=='J' && b=='Q') return true;
    else if(a=='T' && b=='J') return true;
    else 
    {
        try
        {
            if( (b-'0') - (a-'0') == 1)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        catch (std::exception &e)
        {
            return false;
        }
    }
};

bool game::compare_rank(const hand &one, const hand &two)
{
    char a = std::get<0>(one);
    char b = std::get<0>(two);

    if(a=='A')
    {
        return false;
    }
    else if (b=='A')
    {
        return true;
    }

    if(a=='K')
    {
        return false;
    }
    else if(b=='K')
    {
        return true;
    }

    if(a=='Q')
    {
        return false;
    }
    else if (b=='Q')
    {
        return true;
    }

    if(a=='J')
    {
        return false;
    }
    else if(b=='J')
    {
        return true;
    }

    if(a=='T')
    {
        return false;
    }
    else if(b=='T')
    {
        return true;
    }

    else
    {
        return (a-'0') < (b-'0');
    }
};