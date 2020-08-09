#include "UnresolvableListener.h"


using namespace dotenv;
using namespace std;


UnresolvableListener::UnresolvableListener(const string& key, SymbolsTable& symbols_table):
    key(key),
    symbols_table(symbols_table)
{

}


void UnresolvableListener::enterLine(LineParser::LineContext* ctx)
{
    // Clear the stack in case the listener is reused
    resolve_stack.clear();
}


void UnresolvableListener::exitLine(LineParser::LineContext* ctx)
{
    // At this point all the resolve operations have been registered
    resolve_stack.run();
}


void UnresolvableListener::exitVariable(LineParser::VariableContext* ctx)
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

    SymbolRecord& var = symbols_table.at(var_name);

    // If there is more than one substitution operation, they must be performed
    // from end to beginning so position and size indices are maintained
    // constant throughout the different operations
    // Do not mark variables as solved at this point since that would mess with
    // the resolution system by making it think that they are not unresolvable
    if (var.local() and not var.complete())
    {
        SymbolRecord& record = symbols_table.at(key);
        resolve_stack.emplace(record.value(), "", pos, size);
    }
}
