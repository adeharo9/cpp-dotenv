#pragma once


#include "SymbolsTable.h"

#include "antlr4-runtime.h"

#include <fstream>
#include <string>


namespace dotenv
{
    class Parser
    {
    public:

        Parser();
        Parser(const Parser& parser) = default;
        virtual ~Parser() = default;

        void parse(std::istream& is, const bool overwrite = false, const bool interpolate = true);

    private:

        void parse_dotenv(std::istream& is, const bool overwrite);
        void parse_line();
        void resolve_vars();
        void expand_escape();
        void register_env(const bool interpolate) const;

        void report_unresolved_vars();
        void resolve_unresolved_vars();

        void walk_line(const std::string& line, antlr4::tree::ParseTreeListener& listener);

    private:

        size_t unresolved;
        SymbolsTable symbols_table;

        antlr4::tree::ParseTreeWalker walker;

    };
}
