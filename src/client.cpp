/************************************************************
* Philip Glazman                                           *
* Psychic Poker                                            *
* 4/5/2018                                                 *
************************************************************/

#include "stdafx.h"
#include "file_access.h"
#include "game.h"

// To compile: g++ client.cpp game.cpp file_access.cpp -o game -std=c++14
// https://github.com/btccom/Hire/blob/master/exercise/psychic-poker-en.md

// Client Code.
int main()
{
    // Serialization. Access input file.
    file_access file("game.txt");
    
    // Load file.
    if(!file.load_file())
    {
        return EXIT_FAILURE;
    }

    game game_session(file.get_input());

    // Show input.
    game_session.show_input();

    // Ask for hand recommendations.
    game_session.calculate_best_hand();

    // Show output.
    game_session.show_output();

    return EXIT_SUCCESS;
}