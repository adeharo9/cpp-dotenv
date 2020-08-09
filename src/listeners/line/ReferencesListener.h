#pragma once


#include "ReferencesTable.h"
#include "SymbolsTable.h"
#include "LineBaseListener.h"
#include "LineParser.h"

#include <string>


namespace dotenv
{
    class ReferencesListener final: public LineBaseListener
    {
    public:

        ReferencesListener(const std::string& key, ReferencesTable& references_table, SymbolsTable& symbols_table);
        ReferencesListener(const ReferencesListener& symbols_listener) = default;
        virtual ~ReferencesListener() = default;

        virtual void exitVariable(LineParser::VariableContext* ctx) override;

    private:

        static std::string encode_string(const std::string& decoded);

    private:

        const std::string& key;
        ReferencesTable& references_table;
        SymbolsTable& symbols_table;

    };
}
