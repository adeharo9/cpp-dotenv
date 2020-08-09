#include "ExternalResolverListener.h"


using namespace dotenv;
using namespace std;


ExternalResolverListener::ExternalResolverListener(const string& key, SymbolsTable& symbols_table):
    key(key),
    symbols_table(symbols_table)
{

}


void ExternalResolverListener::enterLine(LineParser::LineContext* ctx)
{
    // Clear the stack in case the listener is reused
    resolve_stack.clear();
}


void ExternalResolverListener::exitLine(LineParser::LineContext* ctx)
{
    // At this point all the resolve operations have been registered
    resolve_stack.run();
}


void ExternalResolverListener::exitVariable(LineParser::VariableContext* ctx)
{
    string var_name = ctx->getText();
    size_t pos = ctx->getStart()->getCharPositionInLine();
    size_t size = var_name.size();

    // Format variable name
    if (ctx->BOUNDED_VARIABLE() != nullptr)
    {
        var_name = var_name.substr(2, var_name.size() - 3);
    }
    else if (ctx->UNBOUNDED_VARIABLE() != nullptr)
    {
        var_name = var_name.substr(1, var_name.size() - 1);
    }

    // At this point any found symbol exists on the symbol table
    const SymbolRecord& var = symbols_table.at(var_name);

    // If the found symbol is completely defined and resolved, substitute it in
    // the original string
    if (not var.local() and var.complete())
    {
        SymbolRecord& record = symbols_table.at(key);

        // If there is more than one substitution operation, they must be performed
        // from end to beginning so position and size indices are maintained
        // constant throughout the different operations
        resolve_stack.emplace(record.value(), var.value(), pos, size);
        record.dependency_resolve_one();
    }
}
