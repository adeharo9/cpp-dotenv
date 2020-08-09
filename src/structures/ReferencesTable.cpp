#include "ReferencesTable.h"


using namespace dotenv;


ReferenceRecord::ReferenceRecord(const size_t line, const size_t pos):
    _line(line),
    _pos(pos)
{

}


size_t ReferenceRecord::line() const
{
    return _line;
}


size_t ReferenceRecord::pos() const
{
    return _pos;
}
