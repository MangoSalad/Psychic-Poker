#ifndef FILE_ACCESS_H
#define FILE_ACCESS_H

#include "stdafx.h"

class file_access
{
public:
    
    // Default constructor.
    file_access(std::string a_file_name) : m_file_name(a_file_name) {};

    // Manages serialization - loads hands from file.
    bool load_file();

    // Gets 2d matrix of game hands.
    const std::vector<std::vector<std::string> > get_input();

private:    

    // File name.
    std::string m_file_name;

    // 2d matrix for list of hands.
    std::vector<std::vector<std::string> > m_input;

    // Validates each card from input.
    bool is_valid_input(std::string a_input);

};


#endif