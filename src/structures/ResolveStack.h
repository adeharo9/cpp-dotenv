#pragma once


#include <stack>
#include <string>


namespace dotenv
{
    class ResolveOperation
    {
    public:

        ResolveOperation(std::string& variable, const std::string& substitute, size_t position, size_t size);

        void run();

    private:

        std::string& variable;
        const std::string& substitute;
        size_t position;
        size_t size;
    };

    class ResolveStack: public std::stack<ResolveOperation>
    {

    };
}
