#include "file_access.h"

/**
 * @brief Responsible for loading a file, checking the serialization, and saving the input object.
 * 
 * @return true 
 * @return false 
 */
bool file_access::load_file()
{
    // Ifstream to read file.
    std::ifstream in_file;
    std::string buff;
    std::vector<std::string> file_contents;
    int num_file_lines = 1;

    // Try openning file.
    in_file.open(m_file_name);

    // If file cannot be opened, let the user know.
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
        std::cout<<buff<<std::endl;

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

    
    // Reserve space for 2d matrix.
    m_input.resize(num_file_lines,std::vector<std::string>(10));


    // Create 2d matrix from input.
    try
    {
        for( int i = 0; i < num_file_lines-1; i++)
        { 
            for(int j = 0; j < 10; j++)
            {
                // Check that the card is a valid card.
                if( is_valid_input(file_contents[j+i*10]) )
                {
                    m_input[i][j]=file_contents[j+i*10];   
                }
                else
                {
                    throw std::string("Invalid card included in file. Please check your file.");
                } 
            }            
        };
    }
    catch(std::string &e)
    {
        std::cout << e << std::endl;
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

/**
 * @brief Selector for input.
 * 
 * @return const std::vector<std::vector<std::string> > 
 */
const std::vector<std::vector<std::string> > file_access::get_input()
{
    return m_input;
}