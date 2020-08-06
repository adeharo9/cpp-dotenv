#include "EscapeExpanderListener.h"


using namespace antlr4;
using namespace dotenv;
using namespace std;


EscapeExpanderListener::EscapeExpanderListener(const string& key, SymbolsTable& symbols_table):
    key(key),
    symbols_table(symbols_table)
{

}


void EscapeExpanderListener::exitLine(LineParser::LineContext* ctx)
{
    // At this point all the expand operations have been registered
    while (not expand_stack.empty())
    {
        ReplaceOperation& operation = expand_stack.top();
        operation.run();
        expand_stack.pop();
    }
}


void EscapeExpanderListener::exitContent(LineParser::ContentContext* ctx)
{
    for (tree::TerminalNode* ESC_SEQ: ctx->ESC_SEQ())
    {
        string sequence = ESC_SEQ->getText();
        size_t pos = ESC_SEQ->getSymbol()->getCharPositionInLine();
        size_t size = sequence.size();

        pair<bool, string> expanded = decode_escaped(sequence);

        if (expanded.first)
        {
            SymbolRecord& record = symbols_table.at(key);
            expand_stack.emplace(record.value(), expanded.second, pos, size);
        }
    }
}


pair<bool, string> EscapeExpanderListener::decode_escaped(const std::string& escaped)
{
    bool success = ESC_EQ.find(escaped) != ESC_EQ.end();
    string expanded;

    if (success)
    {
        expanded = ESC_EQ.at(escaped);
    }

    return {success, expanded};
}


const unordered_map<string, string> EscapeExpanderListener::ESC_EQ
{
    { "\\'" , "'"  },
    { "\\\"", "\"" },
    { "\\?" , "?"  },
    { "\\\\", "\\" },
    { "\\a" , "\a" },
    { "\\b" , "\b" },
    { "\\f" , "\f" },
    { "\\n" , "\n" },
    { "\\r" , "\r" },
    { "\\t" , "\t" },
    { "\\v" , "\v" },
    { "\\$" , "$"  }
};
