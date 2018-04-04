#include "stdafx.h"
#include "file_access.h"

// To compile: g++ client.cpp game.cpp file_access.cpp -o game
// https://github.com/btccom/Hire/blob/master/exercise/psychic-poker-en.md

// Client Code.
int main()
{
    file_access file("game.txt");
    file.load_file();
}