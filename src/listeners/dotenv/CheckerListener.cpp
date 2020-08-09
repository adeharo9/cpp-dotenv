#include "CheckerListener.h"

#include "errors.h"


using namespace dotenv;
using namespace std;


CheckerListener::CheckerListener(TreeDecorations& decorations):
    _errored(false),
    decorations(decorations)
{

}


void CheckerListener::enterPair(DotenvParser::PairContext* ctx)
{
    _errored = false;
}


void CheckerListener::exitPair(DotenvParser::PairContext* ctx)
{
    decorations.put_errored(ctx, _errored);
}


void CheckerListener::exitKey(DotenvParser::KeyContext* ctx)
{
    _errored = ctx->export_token != nullptr and ctx->export_token->getText() != EXPORT_TOKEN;

    if (_errored)
    {
        errors::extraneous_input_error(ctx->export_token, {EXPORT_TOKEN});
    }

    decorations.put_errored(ctx, _errored);
}


void CheckerListener::exitValue(DotenvParser::ValueContext* ctx)
{
    decorations.put_errored(ctx, _errored);
}


const string CheckerListener::EXPORT_TOKEN = "export";
