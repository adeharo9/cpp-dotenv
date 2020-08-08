#pragma once


#include "TreeDecorations.h"
#include "DotenvBaseListener.h"
#include "DotenvParser.h"

#include <string>


namespace dotenv
{
    class CheckerListener final: public DotenvBaseListener
    {
    public:

        CheckerListener(TreeDecorations& decorations);
        CheckerListener(const CheckerListener& checker_listener) = default;
        virtual ~CheckerListener() = default;

        virtual void enterPair(DotenvParser::PairContext* ctx) override;
        virtual void exitPair(DotenvParser::PairContext* ctx) override;

        virtual void exitKey(DotenvParser::KeyContext* ctx) override;

        virtual void exitValue(DotenvParser::ValueContext* ctx) override;

    private:

        bool _errored;
        TreeDecorations& decorations;

        static const std::string EXPORT_TOKEN;

    };
}
