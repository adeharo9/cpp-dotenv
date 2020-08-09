#pragma once


#include "ReplaceStack.h"
#include "SymbolsTable.h"
#include "LineBaseListener.h"
#include "LineParser.h"

#include <string>


namespace dotenv
{
    class UndefinedListener final: public LineBaseListener
    {
    public:

        UndefinedListener(const std::string& key, SymbolsTable& symbols_table);
        UndefinedListener(const UndefinedListener& undefined_listener) = default;
        virtual ~UndefinedListener() = default;

        virtual void enterLine(LineParser::LineContext* ctx) override;
        virtual void exitLine(LineParser::LineContext* ctx) override;

        virtual void exitVariable(LineParser::VariableContext* ctx) override;

    private:

        const std::string& key;
        SymbolsTable& symbols_table;
        ReplaceStack resolve_stack;

    };
}
