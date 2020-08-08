#include "Parser.h"

#include "DotenvCheckerListener.h"
#include "ExpanderListener.h"
#include "LineCheckerListener.h"
#include "PairsListener.h"
#include "ResolverListener.h"
#include "SymbolsListener.h"
#include "TreeDecorations.h"
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


dotenv::Parser::Parser():
    unresolved(0)
{

}


void dotenv::Parser::parse(istream& is, const bool overwrite, const bool interpolate)
{
    // Some initialization in case a parser is reused
    unresolved = 0;
    symbols_table.clear();

    parse_dotenv(is, overwrite);

    // Interpolation is the resolution of nested variables
    if (interpolate)
    {
        parse_line();
        resolve_vars();
    }

    expand_escape();
    register_env(overwrite);
}


void dotenv::Parser::parse_dotenv(istream& is, const bool overwrite)
{
    ANTLRInputStream input(is);
    DotenvLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    tokens.fill();

    DotenvParser parser(&tokens);
    tree::ParseTree* tree = parser.dotenv();

    // Decorations on the dotenv parse tree for storing several info
    // throughout listeners
    TreeDecorations dotenv_decorations;

    // Check for errors on the tree
    DotenvCheckerListener checker_listener(dotenv_decorations);
    walker.walk(&checker_listener, tree);

    // Extract raw key-value pairs
    PairsListener pairs_listener(overwrite, symbols_table, dotenv_decorations);
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


void dotenv::Parser::resolve_vars()
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
            report_unresolved_vars();
            resolve_unresolved_vars();
        }
    }
}


void dotenv::Parser::expand_escape()
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


void dotenv::Parser::register_env(const bool overwrite) const
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


void dotenv::Parser::report_unresolved_vars()
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
            LineCheckerListener checker_listener;
            walk_line(record.value(), checker_listener);
        }
    } 
}


void dotenv::Parser::resolve_unresolved_vars()
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


void dotenv::Parser::walk_line(const string& line, tree::ParseTreeListener& listener)
{
    ANTLRInputStream input(line);
    LineLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    tokens.fill();

    LineParser parser(&tokens);
    tree::ParseTree* tree = parser.line();

    walker.walk(&listener, tree);
}
