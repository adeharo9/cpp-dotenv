#pragma once


#include "SymbolsTable.h"
#include "LineBaseListener.h"
#include "LineParser.h"

#include <string>


namespace dotenv
{
    class SymbolsResolverListener final: public LineBaseListener
    {
    public:

        SymbolsResolverListener(const std::string& key, SymbolsTable& symbols_table);

        virtual void enterVariable(LineParser::VariableContext* ctx) override;
        virtual void exitVariable(LineParser::VariableContext* ctx) override;

    private:

        const std::string& key;
        SymbolsTable& symbols_table;

    };
}
