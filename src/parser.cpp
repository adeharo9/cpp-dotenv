#include "parser.h"

#include "PairsTable.h"
#include "PairsListener.h"

#include "DotenvLexer.h"
#include "DotenvParser.h"

#include "antlr4-runtime.h"

using namespace antlr4;
using namespace dotenv;
using namespace std;


parser::parser(istream& is, const bool overwrite):
    overwrite(overwrite),
    is(is)
{

}

void parser::parse()
{
    ANTLRInputStream input(is);
    DotenvLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    tokens.fill();

    DotenvParser parser(&tokens);
    tree::ParseTree* tree = parser.dotenv();

    tree::ParseTreeWalker walker;

    // ErrorsCheckerListener errors_checker;

    // walker.walk(&errors_checker, tree);

    PairsTable pairs_table;
    PairsListener pairs_listener(pairs_table);

    walker.walk(&pairs_listener, tree);
}
