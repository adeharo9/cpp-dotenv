#include "ReplaceStack.h"


using namespace dotenv;
using namespace std;


ReplaceOperation::ReplaceOperation(std::string& original, const string& replace, size_t pos, size_t size):
    original(original),
    replace(replace),
    pos(pos),
    size(size)
{

}


void ReplaceOperation::run()
{
    original.erase(pos, size).insert(pos, replace);
}


void ReplaceStack::clear()
{
    while (not this->empty())
    {
        this->pop();
    }
}


void ReplaceStack::run()
{
    while (not this->empty())
    {
        ReplaceOperation& operation = this->top();
        operation.run();
        this->pop();
    }
}
