#include "Parser.h"

#include "EscapeExpanderListener.h"
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

    // Interpolation is the resolution of nested variables
    if (interpolate)
    {
        parse_line();
        resolve();
    }

    expand();
    register_env();
}


void dotenv::Parser::parse_dotenv()
{
    // Extract raw key-value pairs
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
    for (const pair<string, SymbolRecord>& symbol: symbols_table)
    {
        // std::pair.second returns a copy of the second element, and a
        // reference is needed to check the evolution of the symbol's state,
        // so take it directly from the symbols table
        const string& key = symbol.first;
        const SymbolRecord& record = symbols_table.at(key);

        // If the symbol is local (defined in the .env file being treated),
        // check for dependency on other symbols
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

            // If after the check the symbol has dependency on other symbols,
            // take not of it for later resolving
            if (not record.complete())
            {
                ++unresolved;
            }
        }
    }
}


void dotenv::Parser::resolve()
{
    // If there are no circular dependencies, each iteration should at
    // least resolve one variable, so the loop is expected to finish
    size_t old_unresolved;
    while (unresolved > 0)
    {
        old_unresolved = unresolved;
        for (const pair<string, SymbolRecord>& symbol: symbols_table)
        {
            // std::pair.second returns a copy of the second element, and a
            // reference is needed to check the evolution of the symbol's state,
            // so take it directly from the symbols table
            const string& key = symbol.first;
            const SymbolRecord& record = symbols_table.at(key);

            // If the symbol is local and is not yet resolved, try to resolve
            // it by walking through its dependencies again
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

                // If the symbol is now completed, note it
                if (record.complete())
                {
                    --unresolved;
                }

                // No need to further wait in this situation
                if (unresolved == 0)
                {
                    return;
                }
            }
        }

        // If there are no new variables resolved in an iteration, it means
        // there is at least one circular dependency and thus it cannot be
        // resolved
        if (old_unresolved == unresolved)
        {
            return;
        }
    }
}


void dotenv::Parser::expand()
{
    for (const pair<string, SymbolRecord>& symbol: symbols_table)
    {
        // std::pair.second returns a copy of the second element, and a
        // reference is needed to check the evolution of the symbol's state,
        // so take it directly from the symbols table
        const string& key = symbol.first;
        const SymbolRecord& record = symbols_table.at(key);

        // Expand only escaped sequences in local symbols
        if (record.local())
        {
            ANTLRInputStream input(record.value());
            LineLexer lexer(&input);
            CommonTokenStream tokens(&lexer);
            tokens.fill();

            LineParser parser(&tokens);
            tree::ParseTree* tree = parser.line();

            tree::ParseTreeWalker walker;
            EscapeExpanderListener escape_expander(key, symbols_table);
            walker.walk(&escape_expander, tree);
        }
    }
}


void dotenv::Parser::register_env() const
{
    for (const pair<string, SymbolRecord>& symbol: symbols_table)
    {
        const string& key = symbol.first;
        const SymbolRecord& record = symbols_table.at(key);

        // Register only local symbols (those defined in the .env file)
        if (record.local())
        {
            setenv(key, record.value(), overwrite);
        }
    }
}
