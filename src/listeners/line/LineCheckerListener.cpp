#include "LineCheckerListener.h"

#include "errors.h"


using namespace dotenv;


LineCheckerListener::LineCheckerListener(const size_t line):
    line(line)
{

}


void LineCheckerListener::exitVariable(LineParser::VariableContext* ctx)
{
    if (ctx->BOUNDED_VARIABLE() != nullptr)
    {
        errors::circular_reference_error(ctx->BOUNDED_VARIABLE(), line);
    }
    else if (ctx->UNBOUNDED_VARIABLE() != nullptr)
    {
        errors::circular_reference_error(ctx->UNBOUNDED_VARIABLE(), line);
    }
}
