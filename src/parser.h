#pragma once


#include "antlr4-runtime.h"

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
        antlr4::ANTLRInputStream is;

    };
}
