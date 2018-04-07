#include "game.h"

/**
 * @brief Construct a new game::game object
 * 
 */
game::game()
{

};

/**
 * @brief Construct a new game::game object
 * 
 * @param a_input 
 */
game::game(std::vector<std::vector<std::string> > a_input)
{
    // Size local variable appropriately.
    m_input.resize(a_input.size());

    // Assign a_input to m_input.
    for(int i=0; i<a_input.size(); i++)
    {
        m_input[i].resize(10);
        
        for(int j=0; j<a_input[0].size(); j++)
        {
            if(j<=4)
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

/**
 * @brief Debugging function that shows the input.
 * 
 */
void game::show_input()
{
    std::cout<<"Input"<<std::endl;
    std::cout<<"======================================"<<std::endl;
    
    for(int i=0; i<m_input.size(); i++)
    {
        for(int j=0; j<m_input[0].size(); j++)
        {
            std::cout << std::get<0>(m_input[i][j]) << std::get<1>(m_input[i][j]) << " ";
        }
        std::cout << std::endl;
    }

};

/**
 * @brief Shows the output to the user.
 * 
 */
void game::show_output()
{
    std::cout<<"Output"<<std::endl;
    std::cout<<"======================================"<<std::endl;

    for(int i=0; i<m_input.size()-1; i++)
    {
        for(int j=0; j<m_input[0].size(); j++)
        {
            std::cout << std::get<0>(m_input[i][j]) << std::get<1>(m_input[i][j]) << " ";
        }
        std::cout << m_best_hand[i] << std::endl;
    }

    std::cout<<"======================================"<<std::endl;
};

/**
 * @brief For each hand, checks the best available hand that can be played.
 * 
 */
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
        //needs work.
        else if(is_four_of_a_kind(m_input[i]))
        {
            m_best_hand[i]=FOUR_OF_A_KIND;
        }
        else if(is_full_house(m_input[i]))
        {
            m_best_hand[i]=FULL_HOUSE;
        }
        else if(is_flush(m_input[i]))
        {
            m_best_hand[i]=FLUSH;
        }
        else if(is_straight(m_input[i]))
        {
            m_best_hand[i]=STRAIGHT;
        }
        else if(is_three_of_a_kind(m_input[i]))
        {
            m_best_hand[i]=THREE_OF_A_KIND;
        }
        else if(is_two_pairs(m_input[i]))
        {
            m_best_hand[i]=TWO_PAIRS;
        }
        else if(is_one_pair(m_input[i]))
        {
            m_best_hand[i]=ONE_PAIR;
        }
        else
        {
            m_best_hand[i]=HIGHEST_CARD;
        }
    }
}

/**
 * @brief Checks if the hand is a full house hand.
 * 
 * @param cards 
 * @return true 
 * @return false 
 */
bool game::is_full_house(std::vector<hand> cards)
{
    std::vector<hand> original_cards = cards;

    // Iterators for going through hand and deck cards.
    iter hand_ptr = cards.begin();
    iter deck_ptr = cards.begin()+5;

    // Number of cards with the same rank.
    int num_same_rank=0;
    std::stack<hand> order_of_cards;

    // Iterate through entire hand and deck.
    while(deck_ptr != cards.end()+1)
    {
        // Sort cards in rank order.
        std::sort(cards.begin(),deck_ptr,compare_rank);

        // Iterate through the current set of cards.
        for(int  i = 2; i <= std::distance(cards.begin(),deck_ptr); i++)
        {
            // If there are 4 cards with the same rank.
            if(order_of_cards.size()==5)
            {
                int max_index=0;
                int count_hand_cards =0;

                while(!order_of_cards.empty())
                {
                    int pos = std::distance(original_cards.begin(),std::find(original_cards.begin(),original_cards.end(),order_of_cards.top()));
                    if(max_index < pos) max_index = pos;
                    if(pos < 5) count_hand_cards++;
                    order_of_cards.pop();
                }
                // std::cout<<(max_index-4) + count_hand_cards<<std::endl;

                // if(5-max_index-4 != count_hand_cards)
                // {
                //     return false;
                // }
                if((max_index-4) + count_hand_cards == 5)
                {
                    return true;
                }
            }
            
            if( (std::get<0>(cards[i]) == std::get<0>(cards[i-1]) && 
                std::get<0>(cards[i]) == std::get<0>(cards[i-2]) ) &&
                (order_of_cards.empty() || std::get<0>(cards[i]) != std::get<0>(order_of_cards.top()) ))

            {
                order_of_cards.push(cards[i]);
                order_of_cards.push(cards[i-1]);
                order_of_cards.push(cards[i-2]);
            }

            else if( (std::get<0>(cards[i]) == std::get<0>(cards[i-1])) &&
                (order_of_cards.empty() || std::get<0>(cards[i]) != std::get<0>(order_of_cards.top())))
            {
                order_of_cards.push(cards[i]);
                order_of_cards.push(cards[i-1]);
            }
        }
        // Empty the stacks.
        while(!order_of_cards.empty()) order_of_cards.pop();
        deck_ptr++;
    }
    return false;
}

/**
 * @brief Checks if the hand is a flush hand.
 * 
 * @param cards 
 * @return true 
 * @return false 
 */
bool game::is_flush(std::vector<hand> cards)
{
    std::vector<hand> original_cards = cards;

    // Iterators for going through hand and deck cards.
    iter hand_ptr = cards.begin();
    iter deck_ptr = cards.begin()+5;

    std::stack<hand> same_suit;

    // Iterate through entire hand and deck.
    while(deck_ptr != cards.end()+1)
    {
        // Sort cards in rank order.
        std::sort(cards.begin(),deck_ptr,compare_suit);

        // Iterate through the current set of cards.
        for(int  i = 1; i <= std::distance(cards.begin(),deck_ptr); i++)
        {
            if(same_suit.size()==5)
            {
                int max_index=0;
                int min_index=9;
                int count_hand_cards =0;

                while(!same_suit.empty())
                {
                    int pos = std::distance(original_cards.begin(),std::find(original_cards.begin(),original_cards.end(),same_suit.top()));
                    if(max_index < pos) max_index = pos;
                    if(min_index > pos) min_index = pos; 
                    if(pos < 5) count_hand_cards++;
                    same_suit.pop();
                }

                if((max_index-4) + count_hand_cards == 5)
                {
                    return true;
                }

            }
            
            if(std::get<1>(cards[i]) == std::get<1>(cards[i-1]))
            {
                if(same_suit.empty())
                {
                    same_suit.push(cards[i-1]);
                }
                same_suit.push(cards[i]);
            }
            else if(!same_suit.empty())
            {
                while(!same_suit.empty()) same_suit.pop();
            }
        }

        // Empty the stacks.
        while(!same_suit.empty()) same_suit.pop();
        deck_ptr++;

    }
    return false;
};

bool game::is_straight(std::vector<hand> cards)
{
    std::vector<hand> original_cards = cards;

    // Iterators for going through hand and deck cards.
    iter hand_ptr = cards.begin();
    iter deck_ptr = cards.begin()+5;

    std::stack<hand> sequential_cards;

    // Iterate through entire hand and deck.
    while(deck_ptr != cards.end())
    {
        // Sort cards in rank order.
        std::sort(cards.begin(),deck_ptr,compare_rank);

        // Iterate through the current set of cards.
        for(int  i = 1; i <= std::distance(cards.begin(),deck_ptr); i++)
        {
            if(sequential_cards.size()==5)
            {
                int max_index=0;
                int min_index=9;
                int count_hand_cards =0;

                while(!sequential_cards.empty())
                {
                    int pos = std::distance(original_cards.begin(),std::find(original_cards.begin(),original_cards.end(),sequential_cards.top()));
                    std::cout << std::get<0>(sequential_cards.top()) << std::get<1>(sequential_cards.top()) << " ";
                    if(max_index < pos) max_index = pos;
                    if(min_index > pos) min_index = pos; 
                    if(pos < 5) count_hand_cards++;
                    sequential_cards.pop();
                }
                std::cout<<std::endl;

                if((max_index-4) + count_hand_cards == 5)
                {
                    return true;
                }

            }
            
            if(!sequential_cards.empty() && std::get<0>(sequential_cards.top())<=5 && std::get<0>(cards[i]) == 'A')
            {
                sequential_cards.push(cards[i]);
            }
            else if(std::get<0>(cards[0]) == '2' && std::get<0>(cards[i]) == 'A' && std::get<0>(sequential_cards.top())!='A')
            {
                sequential_cards.push(cards[i]);
            }

            if(is_sequential(std::get<0>(cards[i-1]),std::get<0>(cards[i])) && (sequential_cards.empty() || is_sequential(std::get<0>(sequential_cards.top()),std::get<0>(cards[i-1]))))
            {
                if(sequential_cards.empty())
                {
                    sequential_cards.push(cards[i-1]);
                }
                sequential_cards.push(cards[i]);
            }
        }
        // Empty the stacks.
        while(!sequential_cards.empty()) sequential_cards.pop();
        deck_ptr++;

    }

    return false;
};

bool game::is_three_of_a_kind(std::vector<hand> cards)
{
    std::vector<hand> original_cards = cards;

    // Iterators for going through hand and deck cards.
    iter hand_ptr = cards.begin();
    iter deck_ptr = cards.begin()+5;

    std::stack<hand> pairs;

    // Iterate through entire hand and deck.
    while(deck_ptr != cards.end()+1)
    {
        // Sort cards in rank order.
        std::sort(cards.begin(),deck_ptr,compare_rank);

        // Iterate through the current set of cards.
        for(int  i = 2; i <= std::distance(cards.begin(),deck_ptr); i++)
        {
            if(pairs.size()==3)
            {
                int max_index=0;
                int min_index=9;
                int count_hand_cards =0;

                while(!pairs.empty())
                {
                    int pos = std::distance(original_cards.begin(),std::find(original_cards.begin(),original_cards.end(),pairs.top()));
                    if(max_index < pos) max_index = pos;
                    if(min_index > pos) min_index = pos; 
                    if(pos < 5) count_hand_cards++;
                    pairs.pop();
                }

                if((max_index-4) + count_hand_cards == 5)
                {
                    return true;
                }

            }
            
            if(std::get<0>(cards[i]) == std::get<0>(cards[i-1]) && std::get<0>(cards[i]) == std::get<0>(cards[i-2]))
            {
                pairs.push(cards[i]);
                pairs.push(cards[i-1]);
                pairs.push(cards[i-2]);
            }
        }

        // Empty the stacks.
        while(!pairs.empty()) pairs.pop();
        deck_ptr++;

    }
    return false;
};

bool game::is_two_pairs(std::vector<hand> cards)
{
    std::vector<hand> original_cards = cards;

    // Iterators for going through hand and deck cards.
    iter hand_ptr = cards.begin();
    iter deck_ptr = cards.begin()+5;

    std::stack<hand> pairs;
    int num_pairs = 0;

    // Iterate through entire hand and deck.
    while(deck_ptr != cards.end()+1)
    {
        // Sort cards in rank order.
        std::sort(cards.begin(),deck_ptr,compare_rank);
        num_pairs = 0;

        // Iterate through the current set of cards.
        for(int  i = 1; i <= std::distance(cards.begin(),deck_ptr); i++)
        {
            if(num_pairs==2)
            {
                int max_index=0;
                int count_hand_cards =0;

                while(!pairs.empty())
                {
                    int pos = std::distance(original_cards.begin(),std::find(original_cards.begin(),original_cards.end(),pairs.top()));
                    if(max_index < pos) max_index = pos;
                    if(pos < 5) count_hand_cards++;
                    pairs.pop();
                }

                if((max_index-4) + count_hand_cards == 5)
                {
                    return true;
                }

            }
            
            if(std::get<0>(cards[i]) == std::get<0>(cards[i-1]))
            {
                num_pairs++;
                pairs.push(cards[i]);
                pairs.push(cards[i-1]);
            }
        }

        // Empty the stacks.
        while(!pairs.empty()) pairs.pop();
        deck_ptr++;

    }
    return false;
};

/**
 * @brief Checks if the current hand can be a one pair hand.
 * 
 * @param cards 
 * @return true 
 * @return false 
 */
bool game::is_one_pair(std::vector<hand> cards)
{
    std::vector<hand> original_cards = cards;

    // Iterators for going through hand and deck cards.
    iter hand_ptr = cards.begin();
    iter deck_ptr = cards.begin()+5;

    // Iterate through entire hand and deck.
    while(deck_ptr != cards.end()+1)
    {
        // Sort cards in rank order.
        std::sort(cards.begin(),deck_ptr,compare_rank);

        // Iterate through the current set of cards.
        for(int  i = 1; i <= std::distance(cards.begin(),deck_ptr); i++)
        {
            // If a pair exists in rank.
            if(std::get<0>(cards[i]) == std::get<0>(cards[i-1]))
            {
                // Check to make sure that if the 5th card from the deck is taken, no cards in the pair are from the original hand.
                int first_card = std::distance(original_cards.begin(),std::find(original_cards.begin(),original_cards.end(),cards[i]));
                int second_card = std::distance(original_cards.begin(),std::find(original_cards.begin(),original_cards.end(),cards[i-1]));

                if(std::max(first_card,second_card) == 9 && std::min(first_card,second_card)<5)
                {
                    return false;
                }

                // Cards has one pair.
                return true;
            }
        }
        deck_ptr++;
    }
    return false;
};

/**
 * @brief Checks if hand is a four of a kind hand.
 * 
 * @param cards 
 * @return true 
 * @return false 
 */
bool game::is_four_of_a_kind(std::vector<hand> cards)
{
    std::vector<hand> original_cards = cards;

    // Iterators for going through hand and deck cards.
    iter hand_ptr = cards.begin();
    iter deck_ptr = cards.begin()+5;

    // Number of cards with the same rank.
    int num_same_rank=0;
    std::stack<hand> order_of_cards;

    // Iterate through entire hand and deck.
    while(deck_ptr != cards.end()+1)
    {
        // Sort cards in rank order.
        std::sort(cards.begin(),deck_ptr,compare_rank);

        // Iterate through the current set of cards.
        for(int  i = 3; i <= std::distance(cards.begin(),deck_ptr); i++)
        {
            // If there are 4 cards with the same rank.
            if(order_of_cards.size()==4)
            {
                int max_index=0;
                int count_hand_cards =0;

                while(!order_of_cards.empty())
                {
                    int pos = std::distance(original_cards.begin(),std::find(original_cards.begin(),original_cards.end(),order_of_cards.top()));
                    // std::cout << std::get<0>(order_of_cards.top()) << std::get<1>(order_of_cards.top()) << " ";
                    if(max_index < pos) max_index = pos;
                    if(pos < 5) count_hand_cards++;
                    order_of_cards.pop();
                }
                // std::cout<<std::endl;
                // std::cout<<(max_index-4) + count_hand_cards<<std::endl;

                // if(5-max_index-4 != count_hand_cards)
                // {
                //     return false;
                // }
                if((max_index-4) + count_hand_cards == 5)
                {
                    return true;
                }
            }
            
            if( std::get<0>(cards[i]) == std::get<0>(cards[i-1]) && 
                std::get<0>(cards[i]) == std::get<0>(cards[i-2]) &&
                std::get<0>(cards[i]) == std::get<0>(cards[i-3]))
            {
                order_of_cards.push(cards[i]);
                order_of_cards.push(cards[i-1]);
                order_of_cards.push(cards[i-2]);
                order_of_cards.push(cards[i-3]);
            }
        }
        // Empty the stacks.
        while(!order_of_cards.empty()) order_of_cards.pop();
        deck_ptr++;
    }
    return false;
}

/**
 * @brief Checks if the hand is a straight flush.
 * 
 * @param cards 
 * @return true 
 * @return false 
 */
bool game::is_straight_flush(std::vector<hand> cards)
{
    std::vector<hand> original_cards = cards;
    
    // Iterators for going through hand and deck cards.
    std::vector<hand>::iterator hand_ptr = cards.begin();
    std::vector<hand>::iterator deck_ptr = cards.begin()+5;

    // Stacks for each suit.
    std::stack<int> count_heart;
    std::stack<int> count_diamond;
    std::stack<int> count_club;
    std::stack<int> count_spade;

    // Iterate through entire hand and deck.
    while(deck_ptr != cards.end()+1)
    {
        // Sort cards in suit order.
        std::sort(cards.begin(),deck_ptr,compare_suit);
        
        // Iterate through the current set of cards.
        for(int  i = 0; i <= std::distance(cards.begin(),deck_ptr); i++)
        {
            // If there are 5 cards in a suit, check for sequential property.
            if(count_heart.size() >= 5 || count_diamond.size()  >= 5 || count_club.size()  >= 5 || count_spade.size()  >= 5)
            {
                // Check that ordered deck property is maintained.
                // Cards from original hand + cards from deck = 5.
                if(count_heart.size() >= 5)
                {
                    // Make sure stack is in sequential order.
                    if(is_valid_sequential_stack(cards,count_heart))
                    {
                        if(is_valid_final_hand(cards,count_heart,original_cards))
                        { 
                            return true;
                        }
                    }
                }
                else if(count_diamond.size() >= 5)
                {
                     // Make sure stack is in sequential order.
                    if(is_valid_sequential_stack(cards,count_diamond))
                    {
                        if(is_valid_final_hand(cards,count_diamond,original_cards))
                        { 
                            return true;
                        }
                    }
                }
                else if(count_club.size() >= 5)
                {
                    // Make sure stack is in sequential order.
                    if(is_valid_sequential_stack(cards,count_club))
                    {
                        if(is_valid_final_hand(cards,count_club,original_cards))
                        {
                            return true;
                        }
                    }
                }
                else if(count_spade.size() >= 5)
                {
                     // Make sure stack is in sequential order.
                    if(is_valid_sequential_stack(cards,count_spade))
                    {
                        if(is_valid_final_hand(cards,count_spade,original_cards))
                        {
                            return true;
                        }
                    } 
                } 
            }

            if(std::get<1>(cards[i])  == 'H') count_heart.push(i);
            else if(std::get<1>(cards[i])=='D') count_diamond.push(i);
            else if(std::get<1>(cards[i])=='C') count_club.push(i);
            else if(std::get<1>(cards[i])=='S') count_spade.push(i);
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

/**
 * @brief Performs a check to make sure that # of cards from original hand and # of cards from deck equal 5.
 * 
 * @param final_hand 
 * @param suit_stack 
 * @param original_cards 
 * @return true 
 * @return false 
 */
bool game::is_valid_final_hand(const std::vector<hand> final_hand, std::stack<int> suit_stack,std::vector<hand> original_cards)
{
    int cards_from_hand = 0;
    int cards_from_deck = 0;

    int max_index=0;
    int count_hand_cards=0;
    
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

        int pos = std::distance(original_cards.begin(),std::find(original_cards.begin(),original_cards.end(),final_hand[suit_stack.top()]));
        if(max_index < pos) max_index = pos;
        if(pos < 5) count_hand_cards++;

        suit_stack.pop();
    }

    if((max_index-4) + count_hand_cards == 5)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool game::is_valid_sequential_stack(const std::vector<hand> final_hand, std::stack<int> suit_stack)
{
    char last_card = std::get<0>(final_hand[suit_stack.top()]); 
    suit_stack.pop();

    while(!suit_stack.empty())
    {   
        if(!is_sequential(std::get<0>(final_hand[suit_stack.top()]),last_card))
        {
            return false;
        } 
        last_card = std::get<0>(final_hand[suit_stack.top()]); 
        suit_stack.pop();
    }
    return true;
}

/**
 * @brief Checks if two ranks are in sequential order where a < b.
 * 
 * @param a
 * @param b 
 * @return true 
 * @return false 
 */
bool game::is_sequential(const char a, const char b)
{
    if(a=='A' && b == 'K') return true;
    else if(a=='K' && b=='A') return true;
    else if(a=='Q' && b=='K') return true;
    else if(a=='J' && b=='Q') return true;
    else if(a=='T' && b=='J') return true;
    else if(a=='9' && b=='T') return true;
    else if(a=='2' && b=='A') return true;
    else 
    {
        try
        {
            // if(isalpha(a) || !isalpha(b))
            // {
            //     return true;
            // }
            // else if (!isalpha(a) && isalpha(b))
            // {
            //     return false;
            // }
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

/**
 * @brief Comparator function for ordering a pair of cards by suit.
 * 
 * @param one 
 * @param two 
 * @return true 
 * @return false 
 */
bool game::compare_suit(const hand &one, const hand &two)
{
    // Implicit casting.
    int a = std::get<1>(one);
    int b = std::get<1>(two);

    return a > b;
}

/**
 * @brief Comparator function for ordering a pair of cards by rank.
 * 
 * @param one 
 * @param two 
 * @return true 
 * @return false 
 */
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