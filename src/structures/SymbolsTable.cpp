#include "SymbolsTable.h"


using namespace dotenv;
using namespace std;


SymbolRecord::SymbolRecord(const bool declared,
                           const bool defined,
                           const size_t num_depends,
                           const bool local):
    _declared(declared),
    _defined(defined),
    _local(local),
    _line(0),
    _offset(0),
    _num_depends(num_depends)
{

}


bool SymbolRecord::complete() const
{
    // A complete symbol is a declared, defined and resolved one
    return _declared and _defined and _num_depends == 0;
}


bool SymbolRecord::declared() const
{
    return _declared;
}


bool SymbolRecord::defined() const
{
    return _defined;
}


bool SymbolRecord::resolved() const
{
    // I.e. no dependencies
    return _num_depends == 0;
}


bool SymbolRecord::local() const
{
    return _local;
}


size_t SymbolRecord::line() const
{
    return _line;
}


size_t SymbolRecord::offset() const
{
    return _offset;
}


string& SymbolRecord::value()
{
    return _value;
}


const string& SymbolRecord::value() const
{
    return _value;
}


void SymbolRecord::set_declared()
{
    _declared = true;
}


void SymbolRecord::set_defined()
{
    _defined = true;
}


void SymbolRecord::set_line(const size_t line)
{
    _line = line;
}


void SymbolRecord::set_offset(const size_t offset)
{
    _offset = offset;
}


void SymbolRecord::set_value(const string& value)
{
    // Despite maybe not being resolved, value implies declaration and
    // definition
    if (not _declared)
    {
        _declared = true;
    }

    if (not _defined)
    {
        _defined = true;
    }

    _value = value;
}


void SymbolRecord::dependency_add_one()
{
    ++_num_depends;
}


void SymbolRecord::dependency_resolve_one()
{
    // Make sure to avoid underflow
    if (_num_depends > 0)
    {
        --_num_depends;
    }
}
