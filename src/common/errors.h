#pragma once


#include "logger.h"

#include "antlr4-runtime.h"

#include <string>
#include <vector>


namespace dotenv
{
    class errors
    {
    public:

        static void token_error(antlr4::Token* token, const std::vector<std::string>& expected = {});

    private:

        static logger _log;

    };
}
