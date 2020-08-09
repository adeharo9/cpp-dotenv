#include "errors.h"


using namespace antlr4;
using namespace dotenv;
using namespace std;


void errors::extraneous_input_error(Token* token, const vector<string>& expected)
{
    size_t line = token->getLine();
    size_t pos = token->getCharPositionInLine();
    string msg = "line " + to_string(line) + ":" + to_string(pos) + " extraneous input '" + token->getText() + "'";

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

    _log.error(msg, line, pos);
}


void errors::undefined_reference_error(const string& reference, const size_t line, const size_t pos)
{
    string msg = "line " + to_string(line) + ":" + to_string(pos) + " undefined reference to '" + reference + "'";

    _log.warn(msg, line, pos);
}


void errors::circular_reference_error(const string& reference, const size_t line, const size_t pos)
{
    string msg = "line " + to_string(line) + ":" + to_string(pos) + " unresolvable reference to '" + reference + "'";

    _log.error(msg, line, pos);
}


void errors::flush()
{
    _log.flush();
}


void errors::clear()
{
    _log.clear();
}


logger errors::_log;
