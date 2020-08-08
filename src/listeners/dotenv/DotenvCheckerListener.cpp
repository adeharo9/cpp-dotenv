#include "DotenvCheckerListener.h"

#include "errors.h"


using namespace dotenv;
using namespace std;


DotenvCheckerListener::DotenvCheckerListener(TreeDecorations& decorations):
    _errored(false),
    decorations(decorations)
{

}


void DotenvCheckerListener::enterPair(DotenvParser::PairContext* ctx)
{
    _errored = false;
}


void DotenvCheckerListener::exitPair(DotenvParser::PairContext* ctx)
{
    decorations.put_errored(ctx, _errored);
}


void DotenvCheckerListener::exitKey(DotenvParser::KeyContext* ctx)
{
    _errored = ctx->export_token != nullptr and ctx->export_token->getText() != EXPORT_TOKEN;

    if (_errored)
    {
        errors::extraneous_input_error(ctx->export_token, {EXPORT_TOKEN});
    }

    decorations.put_errored(ctx, _errored);
}


void DotenvCheckerListener::exitValue(DotenvParser::ValueContext* ctx)
{
    decorations.put_errored(ctx, _errored);
}


const string DotenvCheckerListener::EXPORT_TOKEN = "export";
