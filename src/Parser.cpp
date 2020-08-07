#include "Parser.h"

#include "CheckerListener.h"
#include "ExpanderListener.h"
#include "PairsListener.h"
#include "ResolverListener.h"
#include "SymbolsListener.h"
#include "UnresolvedListener.h"

#include "DotenvLexer.h"
#include "DotenvParser.h"
#include "LineLexer.h"
#include "LineParser.h"

#include "environ.h"

#include <utility>


using namespace antlr4;
using namespace dotenv;
using namespace std;


dotenv::Parser::Parser(istream& is, const bool overwrite, const bool interpolate):
    interpolate(interpolate),
    overwrite(overwrite),
    is(is),
    tree(nullptr),
    unresolved(0)
{

}


void dotenv::Parser::parse()
{
    // Some initialization in case a parser is reused
    tree = nullptr;
    unresolved = 0;
    symbols_table.clear();

    check();
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


void dotenv::Parser::check()
{
    CheckerListener checker_listener(dotenv_decorations);
    walk_dotenv(is, checker_listener);
}


void dotenv::Parser::parse_dotenv()
{
    // Extract raw key-value pairs
    PairsListener pairs_listener(overwrite, symbols_table, dotenv_decorations);
    walk_dotenv(is, pairs_listener);
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
            SymbolsListener symbols_listener(key, symbols_table);
            walk_line(record.value(), symbols_listener);

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
                ResolverListener resolver_listener(key, symbols_table);
                walk_line(record.value(), resolver_listener);

                // If the symbol is now completed, note it
                if (record.complete())
                {
                    --unresolved;
                }

                // No need to further wait in this situation
                if (unresolved == 0)
                {
                    break;
                }
            }
        }

        // If there are no new variables resolved in an iteration, it means
        // there is at least one circular dependency and thus it cannot be
        // resolved
        // Solve them by erasing the references on the string
        if (old_unresolved == unresolved)
        {
            resolve_unresolved();
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
            ExpanderListener expander_listener(key, symbols_table);
            walk_line(record.value(), expander_listener);
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


void dotenv::Parser::resolve_unresolved()
{
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
            UnresolvedListener unresolved_listener(key, symbols_table);
            walk_line(record.value(), unresolved_listener);

            // If the symbol is now completed, note it
            if (record.complete())
            {
                --unresolved;
            }
        }
    }
}


void dotenv::Parser::walk_dotenv(istream& dotenv, tree::ParseTreeListener& listener)
{
    ANTLRInputStream input(dotenv);
    DotenvLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    tokens.fill();

    DotenvParser parser(&tokens);
    tree = parser.line();

    walker.walk(&listener, tree);
}


void dotenv::Parser::walk_line(const string& line, tree::ParseTreeListener& listener)
{
    ANTLRInputStream input(line);
    LineLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    tokens.fill();

    LineParser parser(&tokens);
    tree = parser.line();

    walker.walk(&listener, tree);
}
