#include "Parser.h"

#include "PairsListener.h"
#include "SymbolsListener.h"

#include "DotenvLexer.h"
#include "DotenvParser.h"
#include "LineLexer.h"
#include "LineParser.h"

#include "antlr4-runtime.h"
#include "environ.h"

#include <string>
#include <utility>

using namespace dotenv;
using namespace antlr4;
using namespace std;


dotenv::Parser::Parser(istream& is, const bool overwrite, const bool interpolate):
    interpolate(interpolate),
    overwrite(overwrite),
    is(is)
{

}


void dotenv::Parser::parse()
{
    parse_dotenv();
    if (interpolate)
    {
        parse_line();
        resolve();
    }
    register_env();
}


void dotenv::Parser::parse_dotenv()
{
    ANTLRInputStream input(is);
    DotenvLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    tokens.fill();

    DotenvParser parser(&tokens);
    tree::ParseTree* tree = parser.dotenv();

    tree::ParseTreeWalker walker;
    PairsListener pairs_listener(pairs_table);
    walker.walk(&pairs_listener, tree);
}


void dotenv::Parser::parse_line()
{
    for (const pair<key_type, value_type>& record: pairs_table)
    {
        const key_type& key = record.first;
        const value_type& value = record.second;

        ANTLRInputStream input(value);
        LineLexer lexer(&input);
        CommonTokenStream tokens(&lexer);
        tokens.fill();

        LineParser parser(&tokens);
        tree::ParseTree* tree = parser.line();

        tree::ParseTreeWalker walker;
        SymbolsListener symbols_listener(symbols_table);
        walker.walk(&symbols_listener, tree);
    }
}


void dotenv::Parser::resolve()
{

}


void dotenv::Parser::register_env() const
{
    const int _overwrite = overwrite ? 1 : 0;

    for (const pair<key_type, value_type>& record: pairs_table)
    {
        const key_type& key = record.first;
        const value_type& value = record.second;

        setenv(key.c_str(), value.c_str(), _overwrite);
    }
}
