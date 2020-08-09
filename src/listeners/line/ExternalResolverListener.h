#pragma once


#include "ReplaceStack.h"
#include "SymbolsTable.h"
#include "LineBaseListener.h"
#include "LineParser.h"

#include <string>


namespace dotenv
{
    class ExternalResolverListener final: public LineBaseListener
    {
    public:

        ExternalResolverListener(const std::string& key, SymbolsTable& symbols_table);
        ExternalResolverListener(const ExternalResolverListener& resovler_listener) = default;
        virtual ~ExternalResolverListener() = default;

        virtual void enterLine(LineParser::LineContext* ctx) override;
        virtual void exitLine(LineParser::LineContext* ctx) override;

        virtual void exitVariable(LineParser::VariableContext* ctx) override;

    private:

        const std::string& key;
        SymbolsTable& symbols_table;
        ReplaceStack resolve_stack;

    };
}
