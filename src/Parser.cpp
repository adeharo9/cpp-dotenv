#include "Parser.h"

#include "CheckerListener.h"
#include "ExpanderListener.h"
#include "ExternalResolverListener.h"
#include "ReferencesListener.h"
#include "LocalResolverListener.h"
#include "SymbolsListener.h"
#include "TreeDecorations.h"
#include "UndefinedListener.h"
#include "UnresolvableListener.h"

#include "DotenvLexer.h"
#include "DotenvParser.h"
#include "LineLexer.h"
#include "LineParser.h"

#include "environ.h"
#include "errors.h"

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
    errors::clear();

    parse_dotenv(is, overwrite);

    // Interpolation is the resolution of nested variables
    if (interpolate)
    {
        parse_line();
        resolve_vars();
    }

    expand_escape();
    register_env(overwrite);
    errors::flush();
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
    CheckerListener checker_listener(dotenv_decorations);
    walker.walk(&checker_listener, tree);

    // Extract raw key-value pairs
    SymbolsListener symbols_listener(overwrite, symbols_table, dotenv_decorations);
    walker.walk(&symbols_listener, tree);
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
            ReferencesListener references_listener(key, references_table, symbols_table);
            walk_line(record.value(), references_listener);

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
    // First resolve external variables, since they will all be solved on a
    // single iteration given that they are not resolved nor expanded
    resolve_external_vars();

    // External undefined vars will not be resolved in the loop, so solve them
    // at the beginning so other variables depending on them can be resolved
    report_undefined_vars();
    resolve_undefined_vars();

    // If there are no circular dependencies, each iteration should at
    // least resolve one variable, so the loop is expected to finish
    size_t old_unresolved;
    while (unresolved > 0)
    {
        old_unresolved = unresolved;
        resolve_local_vars();

        // If there are no new variables resolved in an iteration, it means
        // there is at least one circular dependency and thus it cannot be
        // resolved
        // Solve them by erasing the references on the string
        if (old_unresolved == unresolved)
        {
            break;
        }
    }

    report_unresolvable_vars();
    resolve_unresolvable_vars();
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


void dotenv::Parser::resolve_local_vars()
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
            LocalResolverListener resolver_listener(key, symbols_table);
            walk_line(record.value(), resolver_listener);

            // If the symbol is now completed, note it
            if (record.complete())
            {
                --unresolved;
            }
        }
    }
}


void dotenv::Parser::resolve_external_vars()
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
            ExternalResolverListener resolver_listener(key, symbols_table);
            walk_line(record.value(), resolver_listener);

            // If the symbol is now completed, note it
            if (record.complete())
            {
                --unresolved;
            }
        }
    }
}


void dotenv::Parser::resolve_undefined_vars()
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
            UndefinedListener undefined_listener(key, symbols_table);
            walk_line(record.value(), undefined_listener);

            // If the symbol is now completed, note it
            if (record.complete())
            {
                --unresolved;
            }
        }
    }
}


void dotenv::Parser::resolve_unresolvable_vars()
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
            UnresolvableListener unresolvable_listener(key, symbols_table);
            walk_line(record.value(), unresolvable_listener);

            // If the symbol is now completed, note it
            if (record.complete())
            {
                --unresolved;
            }
        }
    }
}


void dotenv::Parser::report_undefined_vars()
{
    // Iterate over all the original existing references (for having access to
    // original location data)
    for (const pair<string, ReferenceRecord>& reference: references_table)
    {
        const string& ref_key = reference.first;
        const ReferenceRecord& reference_record = reference.second;
        const SymbolRecord& symbol_record = symbols_table.at(ref_key);

        // If after all the process the reference symbol is still not resolved,
        // it means it is part of a circular reference
        if (not symbol_record.complete() and not symbol_record.local())
        {
            errors::undefined_reference_error(ref_key, reference_record.line(), reference_record.pos());
        }
    }
}


void dotenv::Parser::report_unresolvable_vars()
{
    // Iterate over all the original existing references (for having access to
    // original location data)
    for (const pair<string, ReferenceRecord>& reference: references_table)
    {
        const string& ref_key = reference.first;
        const ReferenceRecord& reference_record = reference.second;
        const SymbolRecord& symbol_record = symbols_table.at(ref_key);

        // If after all the process the reference symbol is still not resolved,
        // it means it is part of a circular reference
        if (not symbol_record.complete() and symbol_record.local())
        {
            errors::circular_reference_error(ref_key, reference_record.line(), reference_record.pos());
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
