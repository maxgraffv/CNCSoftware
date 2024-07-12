#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <ranges>
#include <algorithm>

#include "fileHandling.h"
#include "gcodeFile.h"
#include "gcodeCommand.h"


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

void GCodeFile::printGCodeStr()
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
    toCommandLines();
    parse();
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


void GCodeFile::parse()
{

    std::vector< GCodeCommand> commandLineVec;
    std::string input("");
    std::string current;

    for(int i = 0; i < commandLines.size(); i++)
    {
        input = commandLines[i];
        for (int j = 0; j < input.length(); j++) {
            char c = input[j];

            // If the character is an uppercase letter and current is not empty, push current to result
            if (isalpha(c) && isupper(c) && !current.empty()) {
                GCodeCommand command( current );
                commandLineVec.push_back( command );
                current.clear();
            }
            
            // Append the current character to current substring
            current += c;
        }

        // Add the last accumulated substring to result
        if (!current.empty()) {
            GCodeCommand command( current );
            commandLineVec.push_back( command );
            current.clear();
        }

        command_vec.push_back( commandLineVec );
        commandLineVec.clear();

    }
}



void GCodeFile::printCommands()
{
        for( int i = 0; i < command_vec.size(); i++)
        {
            for(int j = 0; j < command_vec[i].size(); j++)
                if(command_vec[i][j].getPriority() == -1 && command_vec[i][j].getCommandType() != 'N')
                std::cout << command_vec[i][j].getPriority() << "[" << command_vec[i][j].getCommandType() << "]("<<command_vec[i][j].getCommandValue() << ") ";
            // std::cout << std::endl;
        }
}

std::vector< std::vector< GCodeCommand> > GCodeFile::getCommand_vec()
{
    return command_vec;
}


void GCodeFile::sortByPriority()
{
    for(int i = 0; i < command_vec.size(); i++)
    {
        // std::ranges::sort(  );
    }



}