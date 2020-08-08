#pragma once


#include "ReplaceStack.h"
#include "SymbolsTable.h"
#include "LineBaseListener.h"
#include "LineParser.h"

#include <string>


namespace dotenv
{
    class UnresolvedListener final: public LineBaseListener
    {
    public:

        UnresolvedListener(const std::string& key, SymbolsTable& symbols_table);
        UnresolvedListener(const UnresolvedListener& unresolved_listener) = default;
        virtual ~UnresolvedListener() = default;

        virtual void enterLine(LineParser::LineContext* ctx) override;
        virtual void exitLine(LineParser::LineContext* ctx) override;

        virtual void exitVariable(LineParser::VariableContext* ctx) override;

    private:

        const std::string& key;
        SymbolsTable& symbols_table;
        ReplaceStack resolve_stack;

    };
}
