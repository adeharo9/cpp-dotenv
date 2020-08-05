#include "SymbolsInitializerListener.h"

#include "environ.h"


using namespace std;
using namespace dotenv;


SymbolsInitializerListener::SymbolsInitializerListener(const string& key, SymbolsTable& symbols_table):
    key(key),
    symbols_table(symbols_table)
{

}


void SymbolsInitializerListener::enterVariable(LineParser::VariableContext* ctx)
{

}


void SymbolsInitializerListener::exitVariable(LineParser::VariableContext* ctx)
{
    string var_name;

    // Get variable name and positional info
    if (ctx->BOUNDED_VARIABLE() != nullptr)
    {
        var_name += ctx->BOUNDED_VARIABLE()->getText();
        var_name = var_name.substr(2, var_name.size() - 3);
    }
    else if (ctx->UNBOUNDED_VARIABLE() != nullptr)
    {
        var_name += ctx->UNBOUNDED_VARIABLE()->getText();
        var_name = var_name.substr(1, var_name.size() - 1);
    }

    // If the symbol does not exist on the table, it is not local (i.e. it is
    // defined on the outer environment)
    // Retrieve from the environment and register it in the symbols table
    // If it does not exist, it will be retrieved as an empty string
    if (symbols_table.find(var_name) == symbols_table.end())
    {
        SymbolRecord var(true, true, 0, false);
        var.set_value(dotenv::getenv(var_name).second);
        symbols_table.emplace(var_name, var);
    }

    symbols_table.at(key).add_one_dependency();
}
