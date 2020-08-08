#pragma once


#include "logger.h"

#include "antlr4-runtime.h"


namespace dotenv
{
    class errors
    {
    public:

        static void token_error(antlr4::Token* token);

    private:

        static logger _log;

    };
}
