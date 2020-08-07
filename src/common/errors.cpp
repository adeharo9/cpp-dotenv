#include "errors.h"

#include <string>


using namespace antlr4;
using namespace dotenv;
using namespace std;


void errors::token_error(Token* token)
{
    string line = to_string(token->getLine());
    string pos = to_string(token->getCharPositionInLine());
    log.error(line + ":" + pos + " unidentified keyword \"" + token->getText() + "\"");
}


errors::logger log;
