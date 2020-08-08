#pragma once


#include "ReferencesTable.h"
#include "SymbolsTable.h"
#include "TreeDecorations.h"
#include "DotenvBaseListener.h"
#include "DotenvParser.h"

#include <string>


namespace dotenv
{
    class SymbolsListener final: public DotenvBaseListener
    {
    public:

        SymbolsListener(const bool overwrite, SymbolsTable& symbols_table, TreeDecorations& decorations);
        SymbolsListener(const SymbolsListener& pairs_listener) = default;
        virtual ~SymbolsListener() = default;

        virtual void enterPair(DotenvParser::PairContext* ctx) override;
        virtual void exitPair(DotenvParser::PairContext* ctx) override;

        virtual void exitKey(DotenvParser::KeyContext* ctx) override;

        virtual void exitValue(DotenvParser::ValueContext* ctx) override;

    private:

        size_t _line;
        size_t _offset;
        std::string _key;
        std::string _value;

        bool overwrite;
        SymbolsTable& symbols_table;
        TreeDecorations& decorations;

    };
}
