#pragma once


#include "SymbolsTable.h"
#include "LineBaseListener.h"
#include "LineParser.h"

#include <string>


namespace dotenv
{
    class SymbolsListener final: public LineBaseListener
    {
    public:

        SymbolsListener(const std::string& key, SymbolsTable& symbols_table);
        SymbolsListener(const SymbolsListener& symbols_listener) = default;
        virtual ~SymbolsListener() = default;

        virtual void exitVariable(LineParser::VariableContext* ctx) override;

    private:

        const std::string& key;
        SymbolsTable& symbols_table;

    };
}
