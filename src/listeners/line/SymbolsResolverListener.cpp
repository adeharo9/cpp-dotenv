#include "SymbolsResolverListener.h"


using namespace std;
using namespace dotenv;


SymbolsResolverListener::SymbolsResolverListener(const string& key, SymbolsTable& symbols_table):
    key(key),
    symbols_table(symbols_table)
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

        // Start position of the variable substring in the line
        pos = ctx->BOUNDED_VARIABLE()->getSymbol()->getCharPositionInLine();
        size = var_name.size();

        var_name = var_name.substr(2, var_name.size() - 3);
    }
    else if (ctx->UNBOUNDED_VARIABLE() != nullptr)
    {
        var_name += ctx->UNBOUNDED_VARIABLE()->getText();

        // Start position of the variable substring in the line
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

        // Delete the old variable substring, insert the new one and mark it
        // as resolved
        key_var.value().erase(pos, size).insert(pos, var.value());
        key_var.dependency_resolve_one();
    }
}
