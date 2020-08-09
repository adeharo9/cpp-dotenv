#include "SymbolsListener.h"

#include "environ.h"


using namespace dotenv;


SymbolsListener::SymbolsListener(const bool overwrite, SymbolsTable& symbols_table, TreeDecorations& decorations):
    overwrite(overwrite),
    symbols_table(symbols_table),
    decorations(decorations)
{

}


void SymbolsListener::enterPair(DotenvParser::PairContext* ctx)
{
    _line = ctx->getStart()->getLine();
    _offset = 0;
    _key.clear();
    _value.clear();
}


void SymbolsListener::exitPair(DotenvParser::PairContext* ctx)
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
    record.set_line(_line);
    record.set_offset(_offset);
    record.set_value(_value);

    symbols_table.emplace(_key, record);
}


void SymbolsListener::exitKey(DotenvParser::KeyContext* ctx)
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


void SymbolsListener::exitValue(DotenvParser::ValueContext* ctx)
{
    if (decorations.get_errored(ctx))
    {
        return;
    }

    _offset = ctx->getStart()->getCharPositionInLine();
    _value += ctx->getText();
    

    if (ctx->STRING() != nullptr)
    {
        _value = _value.substr(1, _value.size() - 2);
    }
}
