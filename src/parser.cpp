#include "parser.h"

#include "PairsTable.h"
#include "PairsListener.h"

#include "DotenvLexer.h"
#include "DotenvParser.h"

#include <iostream>
using namespace std;

using namespace antlr4;
using namespace dotenv;


parser::parser(std::istream& is, const bool overwrite):
    overwrite(overwrite),
    is(is)
{

}

void parser::parse()
{
    cout << "1" << endl;
    DotenvLexer lexer(&is);
    cout << "2" << endl;
    CommonTokenStream tokens(&lexer);
    cout << "3" << endl;
    tokens.fill();
    cout << "4" << endl;

    DotenvParser parser(&tokens);
    tree::ParseTree* tree = parser.dotenv();

    tree::ParseTreeWalker walker;

    // ErrorsCheckerListener errors_checker;

    // walker.walk(&errors_checker, tree);

    PairsTable pairs_table;
    PairsListener pairs_listener(pairs_table);

    walker.walk(&pairs_listener, tree);
}
