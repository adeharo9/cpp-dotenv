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
    _num_depends(num_depends)
{

}


bool SymbolRecord::complete() const
{
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
    return _num_depends == 0;
}


bool SymbolRecord::local() const
{
    return _local;
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


void SymbolRecord::set_value(const string& value)
{
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


void SymbolRecord::add_one_dependency()
{
    ++_num_depends;
}


void SymbolRecord::resolve_one()
{
    if (_num_depends > 0)
    {
        --_num_depends;
    }
}
