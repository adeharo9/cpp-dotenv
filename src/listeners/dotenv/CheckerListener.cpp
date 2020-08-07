#include "CheckerListener.h"

#include "errors.h"


using namespace dotenv;
using namespace std;


CheckerListener::CheckerListener(TreeDecorations& decorations):
    decorations(decorations)
{

}


void CheckerListener::enterPair(DotenvParser::PairContext* ctx)
{
    errored = false;
}


void CheckerListener::exitPair(DotenvParser::PairContext* ctx)
{
    decorations.put_errored(ctx, errored);
}


void CheckerListener::exitKey(DotenvParser::KeyContext* ctx)
{
    errored = ctx->export_token != nullptr and ctx->export_token->getText() != EXPORT_TOKEN;

    if (errored)
    {
        errors::token_error(ctx->export_token);
    }

    decorations.put_errored(ctx, errored);
}


void CheckerListener::exitValue(DotenvParser::ValueContext* ctx)
{
    decorations.put_errored(ctx, errored);
}


const string CheckerListener::EXPORT_TOKEN = "export";
