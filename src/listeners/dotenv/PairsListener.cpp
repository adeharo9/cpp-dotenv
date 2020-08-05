#include "PairsListener.h"

#include "environ.h"


using namespace dotenv;


PairsListener::PairsListener(const bool overwrite, SymbolsTable& symbols_table):
    overwrite(overwrite),
    symbols_table(symbols_table)
{

}


void PairsListener::enterPair(DotenvParser::PairContext* ctx)
{
    _key.clear();
    _value.clear();
}


void PairsListener::exitPair(DotenvParser::PairContext* ctx)
{
    if (not overwrite and _getenv(_key).first)
    {
        return;
    }

    SymbolRecord record(true, true);
    record.set_value(_value);

    symbols_table.emplace(_key, record);
}


void PairsListener::exitKey(DotenvParser::KeyContext* ctx)
{
    if (ctx->key_unquoted != nullptr)
    {
        _key += ctx->key_unquoted->getText();
    }
    else if (ctx->key_string != nullptr)
    {
        _key += ctx->key_string->getText();
        _key = _key.substr(1, _key.size() - 2);
    }
}


void PairsListener::exitValue(DotenvParser::ValueContext* ctx)
{
    size_t n_unquoted = ctx->UNQUOTED_STRING().size();

    if (n_unquoted > 0)
    {
        for (size_t i = 0; i < n_unquoted; ++i)
        {
            if (i > 0)
            {
                _value += ctx->WS(i-1)->getText();
            }

            _value += ctx->UNQUOTED_STRING(i)->getText();
        }
    }
    else if (ctx->STRING() != nullptr)
    {
        _value += ctx->STRING()->getText();
        _value = _value.substr(1, _value.size() - 2);
    }
}
