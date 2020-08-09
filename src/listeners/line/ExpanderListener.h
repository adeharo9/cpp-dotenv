#pragma once


#include "ReplaceStack.h"
#include "SymbolsTable.h"
#include "LineBaseListener.h"
#include "LineParser.h"

#include <string>
#include <unordered_map>
#include <utility>


namespace dotenv
{
    class ExpanderListener final: public LineBaseListener
    {
    public:

        ExpanderListener(const std::string& key, SymbolsTable& symbols_table);
        ExpanderListener(const ExpanderListener& expander_listener) = default;
        virtual ~ExpanderListener() = default;

        virtual void enterLine(LineParser::LineContext* ctx) override;
        virtual void exitLine(LineParser::LineContext* ctx) override;

        virtual void exitContent(LineParser::ContentContext* ctx) override;

    private:

        const std::string& key;
        SymbolsTable& symbols_table;
        ReplaceStack expand_stack;

    };
}
