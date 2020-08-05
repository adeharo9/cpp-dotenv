#include "ResolveStack.h"


using namespace dotenv;
using namespace std;


ResolveOperation::ResolveOperation(std::string& variable, const string& substitute, size_t position, size_t size):
    variable(variable),
    substitute(substitute),
    position(position),
    size(size)
{

}


void ResolveOperation::run()
{
    variable.erase(position, size).insert(position, substitute);
}
