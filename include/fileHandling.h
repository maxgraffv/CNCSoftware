#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include <vector>
#include <string>


class File
{
    private:
        std::string str;

    public:
        File(std::string const& file_path);
        void read( std::string const& file_path );
        void write( std::string const& file_path );
        std::string getStr();


};


#endif