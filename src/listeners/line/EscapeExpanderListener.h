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
    class EscapeExpanderListener final: public LineBaseListener
    {
    public:

        EscapeExpanderListener(const std::string& key, SymbolsTable& symbols_table);

        virtual void exitLine(LineParser::LineContext* ctx) override;
        virtual void exitContent(LineParser::ContentContext* ctx) override;

    private:

        static std::pair<bool, std::string> decode_escaped(const std::string& escaped);

    private:

        const std::string& key;
        SymbolsTable& symbols_table;
        ReplaceStack expand_stack;

        static const std::unordered_map<std::string, std::string> ESC_EQ;

    };
}
