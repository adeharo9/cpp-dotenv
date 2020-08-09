#pragma once


#include "ReferencesTable.h"
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

        void resolve_local_vars();
        void resolve_external_vars();
        void resolve_undefined_vars();
        void resolve_unresolvable_vars();

        void report_undefined_vars();
        void report_unresolvable_vars();

        void walk_line(const std::string& line, antlr4::tree::ParseTreeListener& listener);

    private:

        size_t unresolved;
        ReferencesTable references_table;
        SymbolsTable symbols_table;

        antlr4::tree::ParseTreeWalker walker;

    };
}
