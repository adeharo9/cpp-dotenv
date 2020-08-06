#pragma once


#include "SymbolsTable.h"

#include <fstream>


namespace dotenv
{
    class Parser
    {
    public:

        Parser(std::istream& is, const bool overwrite = false, const bool interpolate = true);

        void parse();

    private:

        void parse_dotenv();
        void parse_line();
        void resolve();
        void expand();
        void register_env() const;

        bool interpolate;
        bool overwrite;
        std::istream& is;

        size_t unresolved;

        SymbolsTable symbols_table;

    };
}
