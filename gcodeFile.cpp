#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <ranges>

#include "gcodeFile.h"
#include "fileHandling.h"


GCodeFile::GCodeFile( std::string gcode_path )
{
    File gcode_file( gcode_path ); 
    gcodeStr = gcode_file.getStr();
    preprocess();

}


void GCodeFile::semicolonCommentsRemove()
{

    char comment_semicolon_begin = ';';
    char comment_semicolon_end = '\n';

    int comment_semicolon_count = std::ranges::count( gcodeStr, ';');

    for( int i = 0; i < comment_semicolon_count; i++)
    {
        
        for(int j = 0; j < gcodeStr.size(); j++)
        {
            if( gcodeStr[j] == comment_semicolon_begin )
            {
                for( int k = j; k < gcodeStr.size(); k++ )
                {
                    if( gcodeStr[k] == comment_semicolon_end)                    
                    {
                        gcodeStr.erase( gcodeStr.begin()+j, gcodeStr.begin()+k );
                        break;
                    }

                }
                break;

            }
        }
    }
}

void GCodeFile::parenthesisCommentsRemove_byPair()
{

    int left_parenthesis_count = std::ranges::count( gcodeStr, '(' );
    int right_parenthesis_count = std::ranges::count( gcodeStr, ')' );

    int left_parenthesis_index = gcodeStr.find_first_of('(');
    int right_parenthesis_index = gcodeStr.find_first_of(')');

    if( left_parenthesis_count != right_parenthesis_count )
        std::cout << "ERROR - Comments parenthessis ( ) are of different number - file not valid" << std::endl;
    else
    {
       for( int i = 0; i < left_parenthesis_count; i++ )
       {
            for( int j = 0; j < gcodeStr.size(); j++ )
            {
                if( gcodeStr[j] == '(' )
                {
                    left_parenthesis_index = j;
                    for( int k = j; k < gcodeStr.size(); k++)
                    {
                        if( gcodeStr[k] == '(' )
                        {
                            left_parenthesis_index = k;
                        }
                        if( gcodeStr[k] == ')' )
                        {
                            right_parenthesis_index = k;
                            gcodeStr.erase( gcodeStr.begin()+left_parenthesis_index, gcodeStr.begin()+right_parenthesis_index+1 );
                            break;
                        }
                    }
                    break;
                }
            }
       }

    }






}

/*
// TO BE CONTINUED 
void GCodeFile::parenthesisCommentsRemove()
{
    int left_parenthesis_count = std::ranges::count( gcodeStr, '(' );
    int right_parenthesis_count = std::ranges::count( gcodeStr, ')' );

    int left_parenthesis_index = gcodeStr.find_first_of('(');
    int right_parenthesis_index = gcodeStr.find_first_of(')');

    

       for( int i = 0; i < left_parenthesis_count; i++ )
       {



       }
}
*/

void GCodeFile::whiteSpacesRemove()
{

    for( int i = 0; i < gcodeStr.size(); i++)
    {
        if(gcodeStr[i] == 0x20 || // Spaces
        
            gcodeStr[i] == 0x09 || // Horizontal Tabs
            // gcodeStr[i] == 0x0A || //New Line
            gcodeStr[i] == 0x0D // Carriage Return 
        )
        {
            gcodeStr.erase( i, 1 );
            i--;
        }
    }

    for( int i = 1; i < gcodeStr.size(); i++)
    {
        if( gcodeStr[i] == 0x0A && gcodeStr[i-1] == 0x0A)
        {
            gcodeStr.erase(i, 1);
            i--;
        }
    }

}

void GCodeFile::print()
{
    std::string border(20, '#');
    std::cout << border << std::endl;
    for( int i = 0; i < gcodeStr.size(); i++ )
    {
        std::cout << gcodeStr[i];
    }
    std::cout << border << std::endl;
}

void GCodeFile::removePercentSign()
{
    for( int i = 0; i < gcodeStr.size()-1; i++)
    {
        if( gcodeStr[i] == '%' && gcodeStr[i+1] == 0x0A)
        {
            gcodeStr.erase(i, 2);
            i--;
        }
    }
}

void GCodeFile::preprocess()
{
    parenthesisCommentsRemove_byPair();
    semicolonCommentsRemove();
    whiteSpacesRemove();
    removePercentSign();
}


void GCodeFile::toCommandLines()
{

    std::string line("");

    for(int i = 0; i < gcodeStr.size(); i++)
    {
        if( gcodeStr[i] == '\n')
        {
            commandLines.push_back(line);
            line.clear();
        }
        else
            line += gcodeStr[i];
    }

    // for(int i = 0; i < commandLines.size(); i++)
    //     std::cout << "line num: " << i << " " << commandLines[i] << std::endl;

}

// bool isLetter(char c)
// {
//     if( c >= 'A' && c <= 'Z')
//         return true;
//     else
//         return false;
// }

// void GCodeFile::parse()
// {
//     int word_begin_index = 0;
//     int word_end_index = 0;
//     std::vector< GCodeCommand> commandLineVec;
//     std::string word("");
//     std::string line("");

//     for(int i = 0; i < commandLines.size(); i++)
//     {
//         line = commandLines[i];

//         for(int j = 0; j < line.size(); j++)
//         {
//             if( isLetter(line[j]) )
//             {
//                 word += line[j];
//                 for(int k = j+1; k < line.size(); k++)
//                 {

//                     if( isLetter(line[k]) || line[k] == '\n')
//                     {
//                         GCodeCommand command(word);
//                         commandLineVec.push_back( command );
//                         word.clear();
//                         j = k;
//                     }
//                     else
//                     {
//                         word += line[k];
//                     }


//                 }

//             }
//         }

//     }
    


// }