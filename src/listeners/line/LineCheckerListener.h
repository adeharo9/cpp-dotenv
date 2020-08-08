#pragma once


#include "LineBaseListener.h"
#include "LineParser.h"


namespace dotenv
{
    class LineCheckerListener final: public LineBaseListener
    {
    public:

        LineCheckerListener(const size_t line);
        LineCheckerListener(const LineCheckerListener& checker_listener) = default;
        virtual ~LineCheckerListener() = default;

        virtual void exitVariable(LineParser::VariableContext* ctx) override;

    private:

        size_t line;

    };
}
