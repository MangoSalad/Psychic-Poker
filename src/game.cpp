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

bool game::is_flush(std::vector<hand> cards)
{
    std::vector<hand> original_cards = cards;
    
    // Iterators for going through hand and deck cards.
    std::vector<hand>::iterator hand_ptr = cards.begin();
    std::vector<hand>::iterator deck_ptr = cards.begin()+5;

    // Iterate through entire hand and deck.
    while(deck_ptr != cards.end()+1)
    {
        // Sort cards in suit order.
        std::sort(cards.begin(),deck_ptr,compare_rank);
        
        // Iterate through the current set of cards.
        for(int  i = 0; i <= std::distance(cards.begin(),deck_ptr); i++)
        {
            //TODO ADD
        }

        deck_ptr++;
    }
    return false;
};

bool game::is_straight(std::vector<hand> cards)
{
    std::vector<hand> original_cards = cards;
    
    std::set<char> set_of_cards;
    std::stack<int> order_of_cards;
    
    // Iterators for going through hand and deck cards.
    iter hand_ptr = cards.begin();
    iter deck_ptr = cards.begin()+5;

    // Iterate through entire hand and deck.
    while(deck_ptr != cards.end()+1)
    {
        // Sort cards in rank order.
        std::sort(cards.begin(),deck_ptr,compare_rank);
        
        // Iterate through the current set of cards.
        for(int  i = 0; i <= std::distance(cards.begin(),deck_ptr); i++)
        {
            if(set_of_cards.size()>=5)
            {
                //std::sort(set_of_cards.begin(),set_of_cards.end(),compare_rank);
                

                if(is_valid_sequential_stack(cards,order_of_cards))
                {
                    if(is_valid_final_hand(cards,order_of_cards,original_cards))
                    {
                        return true;
                    }
                }
            }

            if(std::find(set_of_cards.begin(),set_of_cards.end(),std::get<0>(cards[i]))==set_of_cards.end())
            {
                set_of_cards.insert(std::get<0>(cards[i]));
                order_of_cards.push(i);
            }
            //TODO ADD
        }
        while(!order_of_cards.empty()) order_of_cards.pop();
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

    std::stack<int> order_of_cards;
    int num_pairs = 0;

    // Iterate through entire hand and deck.
    while(deck_ptr != cards.end()+1)
    {
        // Sort cards in rank order.
        std::sort(cards.begin(),deck_ptr,compare_rank);

        // Iterate through the current set of cards.
        for(int  i = 1; i <= std::distance(cards.begin(),deck_ptr); i++)
        {
            if(num_pairs==2)
            {
                // Add kicker cards.
                if(order_of_cards.size()==4)
                {
                    if(i>=6)
                    {
                        order_of_cards.push(i);
                    }
                    else
                    {
                        for(int j = 0; j <= 5; j++)
                        {
                            if(std::get<0>(cards[j])!=std::get<0>(cards[i]) && std::get<2>(cards[j])==HAND_CARD)
                            {
                                order_of_cards.push(j);
                            } 
                        }
                    }
                }
                
                if(is_valid_final_hand(cards,order_of_cards,original_cards))
                { 
                    return true;
                }   
            }
            if(std::get<0>(cards[i]) == std::get<0>(cards[i-1]))
            {
                num_pairs++;
                order_of_cards.push(i);
                order_of_cards.push(i-1);
            }
        }

        // Empty the stacks.
        while(!order_of_cards.empty()) order_of_cards.pop();
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

    std::stack<int> order_of_cards;
    int num_pairs = 0;

    // Iterate through entire hand and deck.
    while(deck_ptr != cards.end()+1)
    {
        // Sort cards in rank order.
        std::sort(cards.begin(),deck_ptr,compare_rank);

        // Iterate through the current set of cards.
        for(int  i = 1; i <= std::distance(cards.begin(),deck_ptr); i++)
        {
            if(num_pairs==2)
            {
                // Add kicker cards.
                if(order_of_cards.size()==4)
                {
                    if(i>=6)
                    {
                        order_of_cards.push(i);
                    }
                    else
                    {
                        for(int j = 0; j <= 5; j++)
                        {
                            if(std::get<0>(cards[j])!=std::get<0>(cards[i]) && std::get<2>(cards[j])==HAND_CARD)
                            {
                                order_of_cards.push(j);
                            } 
                        }
                    }
                }
                
                if(is_valid_final_hand(cards,order_of_cards,original_cards))
                { 
                    return true;
                }   
            }
            if(std::get<0>(cards[i]) == std::get<0>(cards[i-1]))
            {
                num_pairs++;
                order_of_cards.push(i);
                order_of_cards.push(i-1);
            }
        }

        // Empty the stacks.
        while(!order_of_cards.empty()) order_of_cards.pop();
        deck_ptr++;

    }
    return false;
};

bool game::is_one_pair(std::vector<hand> cards)
{
    std::vector<hand> original_cards = cards;

    // Iterators for going through hand and deck cards.
    iter hand_ptr = cards.begin();
    iter deck_ptr = cards.begin()+5;

    std::stack<int> order_of_cards;

    // Iterate through entire hand and deck.
    while(deck_ptr != cards.end()+1)
    {
        // Sort cards in rank order.
        std::sort(cards.begin(),deck_ptr,compare_rank);

        // Iterate through the current set of cards.
        for(int  i = 1; i <= std::distance(cards.begin(),deck_ptr); i++)
        {
            if(std::get<0>(cards[i]) == std::get<0>(cards[i-1]))
            {
                order_of_cards.push(i);
                order_of_cards.push(i-1);

                // Add kicker cards.
                if(order_of_cards.size()==2)
                {
                    if(i>=6)
                    {
                        order_of_cards.push(i);
                    }
                    else
                    {
                        for(int j = 0; j <= 5; j++)
                        {
                            if(std::get<0>(cards[j])!=std::get<0>(cards[i]) && std::get<2>(cards[j])==HAND_CARD)
                            {
                                order_of_cards.push(j);
                                break;
                            } 
                        }
                    }
                }
                if(is_valid_final_hand(cards,order_of_cards,original_cards))
                { 
                    return true;
                }   
            }
        }

        // Empty the stacks.
        while(!order_of_cards.empty()) order_of_cards.pop();
        deck_ptr++;

    }
    return false;
};

bool game::is_full_house(std::vector<hand> cards)
{
    return false;
};

bool game::is_four_of_a_kind(std::vector<hand> cards)
{
    std::vector<hand> original_cards = cards;

    // Iterators for going through hand and deck cards.
    iter hand_ptr = cards.begin();
    iter deck_ptr = cards.begin()+5;

    // Number of cards with the same rank.
    int num_same_rank=0;
    std::stack<int> order_of_cards;

    // Iterate through entire hand and deck.
    while(deck_ptr != cards.end()+1)
    {
        // Sort cards in rank order.
        std::sort(cards.begin(),deck_ptr,compare_rank);
        num_same_rank=0;

        // Iterate through the current set of cards.
        for(int  i = 1; i <= std::distance(cards.begin(),deck_ptr); i++)
        {
            // If there are 4 cards with the same rank.
            if(num_same_rank==4)
            {
                // Add kicker card.
                if(order_of_cards.size()==4)
                {
                    if(i>=6)
                    {
                        order_of_cards.push(i);
                    }
                    else
                    {
                        for(int j = 0; j <= i; j++)
                        {
                            if(std::get<0>(cards[j])!=std::get<0>(cards[j-1]) && std::get<2>(cards[j])==HAND_CARD)
                            {
                                order_of_cards.push(j);
                                break;
                            } 
                        }
                    }
                }

                for(int  i = 0; i <= std::distance(cards.begin(),deck_ptr); i++)
                {
                    std::cout << std::get<0>(cards[i]) << std::get<1>(cards[i]) << " ";
                }
                std::cout<<std::endl;
                
                if(is_valid_final_hand(cards,order_of_cards,original_cards))
                { 
                    return true;
                }
            }
            
            if(std::get<0>(cards[i]) == std::get<0>(cards[i-1]))
            {
                order_of_cards.push(i);
                num_same_rank++;
            }
        }
        // Empty the stacks.
        while(!order_of_cards.empty()) order_of_cards.pop();
        deck_ptr++;
    }
    return false;
}

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

bool game::is_valid_final_hand(const std::vector<hand> final_hand, std::stack<int> suit_stack, const std::vector<hand> original_cards)
{
    int cards_from_hand = 0;
    int cards_from_deck = 0;

    int max_index=0;
    int min_index=10;
    int max_cards_to_draw;
    
    while(!suit_stack.empty())
    { 
//        std::cout<<std::get<0>(final_hand[suit_stack.top()])<<std::get<1>(final_hand[suit_stack.top()])<<" H"<<suit_stack.top()<<std::endl;
        if(std::get<2>(final_hand[suit_stack.top()]) == HAND_CARD)
        {
            cards_from_hand++;
        }
        else if(std::get<2>(final_hand[suit_stack.top()]) == DECK_CARD)
        {
            cards_from_deck++;
        }

        if(max_index<suit_stack.top()) max_index=suit_stack.top();
        if(min_index>suit_stack.top()) min_index=suit_stack.top();
        suit_stack.pop();
    }
    std::cout << "min " <<std::distance(original_cards.begin(),std::find(original_cards.begin(),original_cards.end(),final_hand[max_index])) << "max " << std::distance(original_cards.begin(),std::find(original_cards.begin(),original_cards.end(),final_hand[min_index]))<<std::endl;
    max_cards_to_draw =std::distance(original_cards.begin(),std::find(original_cards.begin(),original_cards.end(),final_hand[max_index])) - std::distance(original_cards.begin(),std::find(original_cards.begin(),original_cards.end(),final_hand[min_index]))+1;
    std::cout<<"max : "<<max_cards_to_draw<<std::endl;
    if((max_cards_to_draw-cards_from_hand)+cards_from_deck==5)
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

bool game::is_sequential(const char a, const char b)
{
    if(a=='A') return false;
    else if(a=='K' && b=='A') return true;
    else if(a=='Q' && b=='K') return true;
    else if(a=='J' && b=='Q') return true;
    else if(a=='T' && b=='J') return true;
    else if(a=='9' && b=='T') return true;
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

bool game::compare_suit(const hand &one, const hand &two)
{
    int a = std::get<1>(one);
    int b = std::get<1>(two);

    return a > b;
}

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
        // if(!isalpha(a) && isalpha(b))
        // {
        //     return true;
        // }
        // else if(isalpha(a) && !isalpha(b))
        // {
        //     return false;
        // }
        
        return (a-'0') < (b-'0');
    }
};