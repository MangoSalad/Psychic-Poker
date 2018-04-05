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
            m_input[i][j] = std::make_pair(a_input[i][j][0],a_input[i][j][1]);

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
            std::cout << m_input[i][j].first << m_input[i][j].second << " ";
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
            std::cout << m_input[i][j].first << m_input[i][j].second << " ";
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
    std::vector<hand>::iterator hand_ptr = cards.begin();
    std::vector<hand>::iterator deck_ptr = cards.begin()+5;


    int max_cards_from_hand = 5;
    int cards_from_hand = 0;
    int cards_from_deck = 0;

    int num_sequential = 0;

    int count_heart = 0;
    int count_diamond = 0;
    int count_club = 0;
    int count_spade = 0;

    // std::cout << (*hand_ptr).first << (*hand_ptr).second << std::endl;

    // Iterate through entire hand and deck.
    while(deck_ptr != cards.end()+1)
    {
        // Sort cards in sequential order.
        std::sort(cards.begin(),deck_ptr,compare_rank);

        //Check for sequential rank property and same suit.
        for(int  i = 1; i < std::distance(cards.begin(),deck_ptr); i++)
        {
            if(num_sequential == 5 && (count_heart == 5 || count_diamond == 5 || count_club == 5 || count_spade == 5))
            {
                // Confirm that # of cards in hand + # of cards from deck = 5;
            
                // for(int  i = 0; i <= std::distance(cards.begin(),deck_ptr); i++)
                // {
                //     std::cout << cards[i].first << cards[i].second << " ";
                // }
                // std::cout <<"Seq: " << num_sequential <<  std::endl;    
                // std::cout << count_heart << std::endl;
                // std::cout << count_diamond << std::endl;
                // std::cout << count_club << std::endl;
                // std::cout << count_spade << std::endl;
                return true;
            }
            // std::cout << is_sequential(cards[i].first,cards[i+1].first);
            
            // Skip duplicate rank.
            if(cards[i].first == cards[i+1].first)
            {
                if(cards[i+1].second == 'H') count_heart++;
                else if(cards[i+1].second=='D') count_diamond++;
                else if(cards[i+1].second=='C') count_club++;
                else if(cards[i+1].second=='S') count_spade++;
                continue;
            }
            
            if(is_sequential(cards[i].first,cards[i+1].first)) //&& cards[i].second == cards[i+1].second)
            {
                if(cards[i+1].second == 'H') count_heart++;
                else if(cards[i+1].second=='D') count_diamond++;
                else if(cards[i+1].second=='C') count_club++;
                else if(cards[i+1].second=='S') count_spade++;

                num_sequential++;
            }
            else
            {
                num_sequential = 0;
            }
        }
        deck_ptr++;
    }

    // for(int  i = 0; i < std::distance(cards.begin(),deck_ptr); i++)
    // {
    //     std::cout << cards[i].first << cards[i].second << " ";
    // }
    // std::cout <<"Seq: " << num_sequential <<  std::endl;    
    // std::cout << count_heart << std::endl;
    // std::cout << count_diamond << std::endl;
    // std::cout << count_club << std::endl;
    // std::cout << count_spade << std::endl;

    return false;
    // Find sequential list of numbers, and make sure it is same pair.
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
    char a = one.first;
    char b = two.first;

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