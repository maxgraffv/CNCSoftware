#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>
#include "fileHandling.h"


File::File(std::string const& file_path)
{
    read( file_path );
}


void File::read( std::string const& file_to_read_path )
{
    std::filesystem::path filesystemPath(file_to_read_path);
    if(std::filesystem::exists(filesystemPath) )
    {

    std::fstream fstream_file(file_to_read_path, std::ios::in);
    str.clear();

    char c;
    while(fstream_file.get(c) )
            str += c ;

    fstream_file.close();
    }
    else
    {
        std::cout << "file does not exist" << std::endl;
    }

}




void File::write( std::string const& file_to_write_path )
{
    std::fstream fstream_file(file_to_write_path, std::ios::out | std::ios::trunc);
	for(char c : str)
	{
		fstream_file << c;
	}

	fstream_file.close();

}

std::string File::getStr()
{
    return str;
}




