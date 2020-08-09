#pragma once


#include <stack>
#include <string>


namespace dotenv
{
    class ReplaceOperation
    {
    public:

        ReplaceOperation(std::string& original, const std::string& replace, size_t pos, size_t size);
        ReplaceOperation(const ReplaceOperation& replace_operation) = default;
        virtual ~ReplaceOperation() = default;

        void run();

    private:

        std::string& original;
        const std::string replace;
        size_t pos;
        size_t size;
    };

    class ReplaceStack: public std::stack<ReplaceOperation>
    {
    public:

        void clear();
        void run();

    };
}
