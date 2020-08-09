#pragma once


#include "ReplaceStack.h"
#include "SymbolsTable.h"
#include "LineBaseListener.h"
#include "LineParser.h"

#include <string>


namespace dotenv
{
    class LocalResolverListener final: public LineBaseListener
    {
    public:

        LocalResolverListener(const std::string& key, SymbolsTable& symbols_table);
        LocalResolverListener(const LocalResolverListener& resovler_listener) = default;
        virtual ~LocalResolverListener() = default;

        virtual void enterLine(LineParser::LineContext* ctx) override;
        virtual void exitLine(LineParser::LineContext* ctx) override;

        virtual void exitVariable(LineParser::VariableContext* ctx) override;

    private:

        const std::string& key;
        SymbolsTable& symbols_table;
        ReplaceStack resolve_stack;

    };
}
