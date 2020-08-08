#pragma once


#include "ReferencesTable.h"
#include "LineBaseListener.h"
#include "LineParser.h"


namespace dotenv
{
    class LineCheckerListener final: public LineBaseListener
    {
    public:

        LineCheckerListener(ReferencesTable& references_table);
        LineCheckerListener(const LineCheckerListener& checker_listener) = default;
        virtual ~LineCheckerListener() = default;

        virtual void exitVariable(LineParser::VariableContext* ctx) override;

    private:

        ReferencesTable& references_table;

    };
}
