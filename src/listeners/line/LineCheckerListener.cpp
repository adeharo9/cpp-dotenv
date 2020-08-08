#include "LineCheckerListener.h"

#include "errors.h"


using namespace dotenv;


void LineCheckerListener::exitVariable(LineParser::VariableContext* ctx)
{
    if (ctx->BOUNDED_VARIABLE() != nullptr)
    {
        errors::circular_reference_error(ctx->BOUNDED_VARIABLE());
    }
    else if (ctx->UNBOUNDED_VARIABLE() != nullptr)
    {
        errors::circular_reference_error(ctx->UNBOUNDED_VARIABLE());
    }
}
