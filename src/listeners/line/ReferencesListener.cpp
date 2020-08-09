#include "ReferencesListener.h"

#include "environ.h"
#include "escape.h"

#include <utility>


using namespace dotenv;
using namespace std;


ReferencesListener::ReferencesListener(const string& key, ReferencesTable& references_table, SymbolsTable& symbols_table):
    key(key),
    references_table(references_table),
    symbols_table(symbols_table)
{

}


void ReferencesListener::exitVariable(LineParser::VariableContext* ctx)
{
    string var_name = ctx->getText();
    size_t pos = ctx->getStart()->getCharPositionInLine();

    // Format variable name
    if (ctx->BOUNDED_VARIABLE() != nullptr)
    {
        var_name = var_name.substr(2, var_name.size() - 3);
    }
    else if (ctx->UNBOUNDED_VARIABLE() != nullptr)
    {
        var_name = var_name.substr(1, var_name.size() - 1);
    }

    // If the symbol does not exist on the table, it is not local (i.e. it is
    // defined on the outer environment)
    // Retrieve it from the environment and register it in the symbols table
    // If it does not exist, add it as not complete in the symbols table
    if (symbols_table.find(var_name) == symbols_table.end())
    {
        pair<bool, string> result = getenv(var_name);
        SymbolRecord var(result.first, result.first, 0, false);

        // Only add value if it had one and escape-encode it so its value is
        // not altered by variable resolution nor escape sequence expansion
        if (result.first)
        {
            var.set_value(encode_string(result.second));
        }
        symbols_table.emplace(var_name, var);
    }

    // Add one dependency
    SymbolRecord& symbol_record = symbols_table.at(key);
    symbol_record.dependency_add_one();

    ReferenceRecord reference_record(symbol_record.line(), symbol_record.offset() + pos);
    references_table.emplace(var_name, reference_record);
}


string ReferencesListener::encode_string(const string& decoded)
{
    // Encode string backwards so indices are not changed by in-place
    // substitutions
    string encoded(decoded);

    for (long i = encoded.size() - 1; i >= 0; --i)
    {
        pair<bool, string> result = escape::encode_escape(encoded.at(i));

        if (result.first)
        {
            encoded.erase(i, 1).insert(i, result.second);
        }
    }

    return encoded;
}
