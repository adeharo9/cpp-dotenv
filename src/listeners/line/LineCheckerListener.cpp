#include "LineCheckerListener.h"

#include "errors.h"

#include <string>


using namespace antlr4;
using namespace dotenv;
using namespace std;


LineCheckerListener::LineCheckerListener(ReferencesTable& references_table):
    references_table(references_table)
{

}


void LineCheckerListener::exitVariable(LineParser::VariableContext* ctx)
{
    tree::TerminalNode* node;
    string var_name = ctx->getText();

    if (ctx->BOUNDED_VARIABLE() != nullptr)
    {
        node = ctx->BOUNDED_VARIABLE();
        var_name = var_name.substr(2, var_name.size() - 3);
    }
    else if (ctx->UNBOUNDED_VARIABLE() != nullptr)
    {
        node = ctx->UNBOUNDED_VARIABLE();
        var_name = var_name.substr(1, var_name.size() - 1);
    }

    ReferenceRecord& record = references_table.at(var_name);

    errors::circular_reference_error(node, record.line(), record.pos());
}
