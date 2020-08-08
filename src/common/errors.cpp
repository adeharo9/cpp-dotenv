#include "errors.h"


using namespace antlr4;
using namespace dotenv;
using namespace std;


void errors::extraneous_input_error(Token* token, const vector<string>& expected)
{
    string line = to_string(token->getLine());
    string pos = to_string(token->getCharPositionInLine());
    string msg = "line " + line + ":" + pos + " extraneous input '" + token->getText() + "'";

    if (not expected.empty())
    {
        msg += " expecting {";
        for (const string& s: expected)
        {
            msg += s;
            msg += ", ";
        }
        msg.erase(msg.size() - 2, 2);
        msg += "}";
    }

    _log.error(msg);
}


void errors::circular_reference_error(tree::TerminalNode* node, const size_t line)
{
    string pos = to_string(node->getSymbol()->getCharPositionInLine());
    string msg = "line " + to_string(line) + ":" + pos + " circular reference '" + node->getText() + "'";

    _log.warn(msg);
}


logger errors::_log;
