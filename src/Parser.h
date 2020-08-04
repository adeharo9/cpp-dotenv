#pragma once


#include "PairsTable.h"
#include "SymbolsTable.h"

#include <fstream>


namespace dotenv
{
    class Parser
    {
    private:

        using   key_type = std::string;
        using value_type = std::string;

    public:

        Parser(std::istream& is, const bool overwrite = false, const bool interpolate = true);

        void parse();

    private:

        void parse_dotenv();
        void parse_line();
        void resolve();
        void register_env() const;

        bool interpolate;
        bool overwrite;
        std::istream& is;

        PairsTable pairs_table;
        SymbolsTable symbols_table;

    };
}
