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

        SymbolsListener(SymbolsTable& symbols_table);

    private:

        SymbolsTable& symbols_table;

    };
}
