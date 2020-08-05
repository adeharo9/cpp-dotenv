#include "SymbolsResolverListener.h"


using namespace std;
using namespace dotenv;


SymbolsResolverListener::SymbolsResolverListener(const string& key, SymbolsTable& symbols_table):
    key(key),
    symbols_table(symbols_table)
{

}


void SymbolsResolverListener::enterVariable(LineParser::VariableContext* ctx)
{

}


void SymbolsResolverListener::exitVariable(LineParser::VariableContext* ctx)
{
    size_t pos;
    size_t size;
    string var_name;

    // Get variable name and positional info
    if (ctx->BOUNDED_VARIABLE() != nullptr)
    {
        var_name += ctx->BOUNDED_VARIABLE()->getText();

        pos = ctx->BOUNDED_VARIABLE()->getSymbol()->getCharPositionInLine();
        size = var_name.size();

        var_name = var_name.substr(2, var_name.size() - 3);
    }
    else if (ctx->UNBOUNDED_VARIABLE() != nullptr)
    {
        var_name += ctx->UNBOUNDED_VARIABLE()->getText();

        pos = ctx->UNBOUNDED_VARIABLE()->getSymbol()->getCharPositionInLine();
        size = var_name.size();

        var_name = var_name.substr(1, var_name.size() - 1);
    }

    // At this point any found symbol exists on the symbol table
    const SymbolRecord& var = symbols_table.at(var_name);

    // If the found symbol is completely defined and resolved, substitute it in
    // the original string
    if (var.complete())
    {
        SymbolRecord& key_var = symbols_table.at(this->key);

        key_var.value().erase(pos, size).insert(pos, var.value());
        key_var.resolve_one();
    }
}
