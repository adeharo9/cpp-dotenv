#pragma once


#include "SymbolsTable.h"
#include "TreeDecorations.h"

#include "antlr4-runtime.h"

#include <fstream>
#include <string>


namespace dotenv
{
    class Parser
    {
    public:

        Parser(std::istream& is, const bool overwrite = false, const bool interpolate = true);

        void parse();

    private:

        void check();
        void parse_dotenv();
        void parse_line();
        void resolve();
        void expand();
        void register_env() const;

        void resolve_unresolved();

        void walk_dotenv(std::istream& dotenv, antlr4::tree::ParseTreeListener& listener);
        void walk_line(const std::string& line, antlr4::tree::ParseTreeListener& listener);

    private:

        bool interpolate;
        bool overwrite;
        std::istream& is;

        antlr4::tree::ParseTree* tree;
        antlr4::tree::ParseTreeWalker walker;

        size_t unresolved;
        SymbolsTable symbols_table;
        TreeDecorations dotenv_decorations;

    };
}
