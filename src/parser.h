#pragma once


#include <fstream>


namespace dotenv
{
    class parser
    {
    public:

        parser(std::istream& is, const bool overwrite = false);

        void parse();

    private:

        bool overwrite;
        std::istream& is;

    };
}
