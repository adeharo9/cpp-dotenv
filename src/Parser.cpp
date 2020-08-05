#include "Parser.h"

#include "PairsListener.h"
#include "SymbolsInitializerListener.h"
#include "SymbolsResolverListener.h"

#include "DotenvLexer.h"
#include "DotenvParser.h"
#include "LineLexer.h"
#include "LineParser.h"

#include "antlr4-runtime.h"
#include "environ.h"

#include <string>
#include <utility>


using namespace antlr4;
using namespace dotenv;
using namespace std;


dotenv::Parser::Parser(istream& is, const bool overwrite, const bool interpolate):
    interpolate(interpolate),
    overwrite(overwrite),
    is(is),
    unresolved(0)
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
    PairsListener pairs_listener(overwrite, symbols_table);
    walker.walk(&pairs_listener, tree);
}


void dotenv::Parser::parse_line()
{
    for (const pair<key_type, SymbolRecord>& symbol: symbols_table)
    {
        const key_type& key = symbol.first;
        const SymbolRecord& record = symbol.second;

        if (record.local())
        {
            ANTLRInputStream input(record.value());
            LineLexer lexer(&input);
            CommonTokenStream tokens(&lexer);
            tokens.fill();

            LineParser parser(&tokens);
            tree::ParseTree* tree = parser.line();

            tree::ParseTreeWalker walker;
            SymbolsInitializerListener symbols_initializer(key, symbols_table);
            walker.walk(&symbols_initializer, tree);

            if (not record.complete())
            {
                ++unresolved;
            }
        }
    }
}


void dotenv::Parser::resolve()
{
    size_t old_unresolved;
    while (unresolved > 0)
    {
        old_unresolved = unresolved;
        for (const pair<key_type, SymbolRecord>& symbol: symbols_table)
        {
            const key_type& key = symbol.first;
            const SymbolRecord& record = symbol.second;

            if (record.local() and not record.complete())
            {
                ANTLRInputStream input(record.value());
                LineLexer lexer(&input);
                CommonTokenStream tokens(&lexer);
                tokens.fill();

                LineParser parser(&tokens);
                tree::ParseTree* tree = parser.line();

                tree::ParseTreeWalker walker;
                SymbolsResolverListener symbols_resolver(key, symbols_table);
                walker.walk(&symbols_resolver, tree);

                if (record.complete())
                {
                    --unresolved;
                }

                if (unresolved == 0)
                {
                    return;
                }
            }
        }

        // If there are no circular dependencies, each iteration should at
        // least resolve one variable
        // If there are no new variables resolved, it means there is circular
        // dependency and thus cannot be resolved
        if (old_unresolved == unresolved)
        {
            return;
        }
    }
}


void dotenv::Parser::register_env() const
{
    for (const pair<key_type, SymbolRecord>& symbol: symbols_table)
    {
        const key_type& key = symbol.first;
        const SymbolRecord& record = symbol.second;

        if (record.local())
        {
            setenv(key, record.value(), overwrite);
        }
    }
}
