#pragma once


#include "antlr4-runtime.h"


namespace dotenv
{
    class TreeDecorations
    {
    public:

        TreeDecorations() = default;
        TreeDecorations(const TreeDecorations& tree_decorations) = default;
        virtual ~TreeDecorations() = default;

        bool get_errored(antlr4::ParserRuleContext* ctx);
        void put_errored(antlr4::ParserRuleContext* ctx, bool errored);

    private:

        antlr4::tree::ParseTreeProperty<bool> _errored;

    };
}
