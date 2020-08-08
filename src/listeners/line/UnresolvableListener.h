#pragma once


#include "ReplaceStack.h"
#include "SymbolsTable.h"
#include "LineBaseListener.h"
#include "LineParser.h"

#include <string>


namespace dotenv
{
    class UnresolvableListener final: public LineBaseListener
    {
    public:

        UnresolvableListener(const std::string& key, SymbolsTable& symbols_table);
        UnresolvableListener(const UnresolvableListener& unresolvable_listener) = default;
        virtual ~UnresolvableListener() = default;

        virtual void enterLine(LineParser::LineContext* ctx) override;
        virtual void exitLine(LineParser::LineContext* ctx) override;

        virtual void exitVariable(LineParser::VariableContext* ctx) override;

    private:

        const std::string& key;
        SymbolsTable& symbols_table;
        ReplaceStack resolve_stack;

    };
}
