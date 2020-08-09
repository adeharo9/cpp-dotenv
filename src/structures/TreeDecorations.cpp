#include "TreeDecorations.h"


using namespace dotenv;


bool TreeDecorations::get_errored(antlr4::ParserRuleContext* ctx)
{
    return _errored.get(ctx);
}


void TreeDecorations::put_errored(antlr4::ParserRuleContext* ctx, bool errored)
{
    _errored.put(ctx, errored);
}
