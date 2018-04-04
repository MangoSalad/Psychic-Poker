#include "file_access.h"

bool file_access::load_file()
{
    std::ifstream in_file;
    std::string buff;
    std::vector<std::string> file_contents;
    int num_file_lines = 1;

    // Try openning file.
    in_file.open(m_file_name);

    if(!in_file)
    {
        std::cout << "Cannot access file." << std::endl;
        return false;
    }

    // Read entire file line by line and parse line using istringstream.
    while(!in_file.eof())
    {
        getline(in_file, buff);
        std::istringstream line(buff);

        while(line)
        {
            buff.clear();
            line >> buff;
            if(buff!="")
            {    
                file_contents.push_back(buff);
            }
        }
        num_file_lines++;
    }

    // Resize 2d matrix.
    m_input.resize(num_file_lines);
    for(int i = 0; i < num_file_lines; i ++)
    {
        m_input[i].resize(num_file_lines);
    }

    // Create 2d matrix from input.
    try
    {
        for(int i = 0; i < file_contents.size(); i++)
        { 
            // Check that valid card is given.
            if( is_valid_input(file_contents[i]) )
            {
                int row = i/num_file_lines;
                int column =  i%num_file_lines;
                m_input[row][column] = file_contents[i];                
            }
            else
            {
                throw;
            } 
        };
    }
    catch(std::exception &e)
    {
        std::cout << "Invalid file format. Please check your file. " << std::endl;
        return false;
    }

    return true;
}

/**
 * @brief Checks that the provided card is a valid card.
 * 
 * @param a_input, string representing card.
 * @return true 
 * @return false 
 */
bool file_access::is_valid_input(std::string a_input)
{
    // Card.
    switch(a_input[0])
    {
        case 'A':
        break;
        case '2':
        break;
        case '3':
        break;
        case '4':
        break;
        case '5':
        break;
        case '6':
        break;
        case '7':
        break;
        case '8':
        break;
        case '9':
        break;
        case 'T':
        break;
        case 'J':
        break;
        case 'Q':
        break;
        case 'K':
        break;
        default:
        return false;
    }

    // Suit.
    switch (a_input[1])
    {
        case 'C':
        break;
        case 'D':
        break;
        case 'H':
        break;
        case 'S':
        break;
        default:
        return false;
    }

    return true;
}

const std::vector<std::vector<std::string> > file_access::get_input()
{
    return m_input;
}