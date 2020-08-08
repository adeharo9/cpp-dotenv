#pragma once


#include "LineBaseListener.h"
#include "LineParser.h"


namespace dotenv
{
    class LineCheckerListener final: public LineBaseListener
    {
    public:

        LineCheckerListener() = default;
        LineCheckerListener(const LineCheckerListener& checker_listener) = default;
        virtual ~LineCheckerListener() = default;

        virtual void exitVariable(LineParser::VariableContext* ctx) override;

    };
}
