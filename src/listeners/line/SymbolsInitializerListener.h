#pragma once


#include "SymbolsTable.h"
#include "LineBaseListener.h"
#include "LineParser.h"

#include <string>


namespace dotenv
{
    class SymbolsInitializerListener final: public LineBaseListener
    {
    public:

        SymbolsInitializerListener(const std::string& key, SymbolsTable& symbols_table);

        virtual void exitVariable(LineParser::VariableContext* ctx) override;

    private:

        const std::string& key;
        SymbolsTable& symbols_table;

    };
}
