#pragma once


#include "SymbolsTable.h"
#include "DotenvBaseListener.h"
#include "DotenvParser.h"

#include <string>


namespace dotenv
{
    class PairsListener final: public DotenvBaseListener
    {
    public:

        PairsListener(const bool overwrite, SymbolsTable& symbols_table);

        virtual void enterPair(DotenvParser::PairContext* ctx) override;
        virtual void exitPair(DotenvParser::PairContext* ctx) override;

        virtual void enterKey(DotenvParser::KeyContext* ctx) override;
        virtual void exitKey(DotenvParser::KeyContext* ctx) override;

        virtual void exitValue(DotenvParser::ValueContext* ctx) override;

    private:

        bool _errored;
        std::string _key;
        std::string _value;

        bool overwrite;
        SymbolsTable& symbols_table;

    };
}
