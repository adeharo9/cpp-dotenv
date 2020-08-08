#include "UndefinedListener.h"


using namespace dotenv;
using namespace std;


UndefinedListener::UndefinedListener(const string& key, SymbolsTable& symbols_table):
    key(key),
    symbols_table(symbols_table)
{

}


void UndefinedListener::enterLine(LineParser::LineContext* ctx)
{
    // Clear the stack in case the listener is reused
    resolve_stack.clear();
}


void UndefinedListener::exitLine(LineParser::LineContext* ctx)
{
    // At this point all the resolve operations have been registered
    resolve_stack.run();
}


void UndefinedListener::exitVariable(LineParser::VariableContext* ctx)
{
    size_t pos;
    size_t size;
    string var_name = ctx->getText();

    // Get variable positional info
    if (ctx->BOUNDED_VARIABLE() != nullptr)
    {
        // Start position of the variable substring in the line
        pos = ctx->BOUNDED_VARIABLE()->getSymbol()->getCharPositionInLine();
        size = ctx->BOUNDED_VARIABLE()->getText().size();

        var_name = var_name.substr(2, var_name.size() - 3);
    }
    else if (ctx->UNBOUNDED_VARIABLE() != nullptr)
    {
        // Start position of the variable substring in the line
        pos = ctx->UNBOUNDED_VARIABLE()->getSymbol()->getCharPositionInLine();
        size = ctx->UNBOUNDED_VARIABLE()->getText().size();

        var_name = var_name.substr(1, var_name.size() - 1);
    }

    SymbolRecord& var = symbols_table.at(var_name);

    // If there is more than one substitution operation, they must be performed
    // from end to beginning so position and size indices are maintained
    // constant throughout the different operations
    if (not var.local() and not var.complete())
    {
        SymbolRecord& record = symbols_table.at(key);
        resolve_stack.emplace(record.value(), "", pos, size);
        record.dependency_resolve_one();
    }
}
