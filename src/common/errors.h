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

        static void extraneous_input_error(antlr4::Token* token, const std::vector<std::string>& expected = {});
        static void circular_reference_error(antlr4::tree::TerminalNode* node, const size_t line);

        static void flush();
        static void clear();

    private:

        static logger _log;

    };
}
