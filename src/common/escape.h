#pragma once


#include <string>
#include <unordered_map>
#include <utility>


namespace dotenv
{
    class escape
    {
    public:

        static std::pair<bool, std::string> encode_escape(const char sequence);
        static std::pair<bool, std::string> encode_escape(const std::string& sequence);
        static std::pair<bool, std::string> decode_escape(const std::string& sequence);

    private:

        static const std::unordered_map<std::string, std::string> ENC_ESC_EQ;
        static const std::unordered_map<std::string, std::string> DEC_ESC_EQ;

    };
}
