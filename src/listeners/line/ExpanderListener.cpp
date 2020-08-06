#include "ExpanderListener.h"


using namespace antlr4;
using namespace dotenv;
using namespace std;


ExpanderListener::ExpanderListener(const string& key, SymbolsTable& symbols_table):
    key(key),
    symbols_table(symbols_table)
{

}


void ExpanderListener::enterLine(LineParser::LineContext* ctx)
{
    // Clear the stack in case the listener is reused
    expand_stack.clear();
}


void ExpanderListener::exitLine(LineParser::LineContext* ctx)
{
    // At this point all the expand operations have been registered
    expand_stack.run();
}


void ExpanderListener::exitContent(LineParser::ContentContext* ctx)
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


pair<bool, string> ExpanderListener::decode_escaped(const std::string& escaped)
{
    bool success = ESC_EQ.find(escaped) != ESC_EQ.end();
    string expanded;

    if (success)
    {
        expanded = ESC_EQ.at(escaped);
    }

    return {success, expanded};
}


const unordered_map<string, string> ExpanderListener::ESC_EQ
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
