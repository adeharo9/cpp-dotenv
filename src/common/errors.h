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
        static void undefined_reference_error(const std::string& reference, const size_t line, const size_t pos);
        static void circular_reference_error(const std::string& reference, const size_t line, const size_t pos);

        static void flush();
        static void clear();

    private:

        static logger _log;

    };
}
