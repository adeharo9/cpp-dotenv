#include "PairsListener.h"

#include "environ.h"


using namespace dotenv;


PairsListener::PairsListener(const bool overwrite, SymbolsTable& symbols_table, TreeDecorations& decorations):
    overwrite(overwrite),
    symbols_table(symbols_table),
    decorations(decorations)
{

}


void PairsListener::enterPair(DotenvParser::PairContext* ctx)
{
    _key.clear();
    _value.clear();
}


void PairsListener::exitPair(DotenvParser::PairContext* ctx)
{
    // If there was some kind of parsing error due by rules not detectable
    // by lexer or parser, do not add the pair to the symbol table
    if (decorations.get_errored(ctx))
    {
        return;
    }

    // If overwrite is turned off and the environment variable already
    // exists, do not record it on the symbols table
    // Later on, during resolution, it will be brought from the external
    // environment, just as expected
    if (not overwrite and getenv(_key).first)
    {
        return;
    }

    SymbolRecord record;
    record.set_line(ctx->getStart()->getLine());
    record.set_value(_value);

    symbols_table.emplace(_key, record);
}


void PairsListener::exitKey(DotenvParser::KeyContext* ctx)
{
    if (decorations.get_errored(ctx))
    {
        return;
    }

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
    if (decorations.get_errored(ctx))
    {
        return;
    }

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
