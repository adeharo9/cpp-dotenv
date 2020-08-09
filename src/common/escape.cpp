#include "escape.h"


using namespace dotenv;
using namespace std;


pair<bool, string> escape::encode_escape(const char sequence)
{
    return escape::encode_escape(string(1, sequence));
}


pair<bool, string> escape::encode_escape(const std::string& sequence)
{
    bool success = ENC_ESC_EQ.find(sequence) != ENC_ESC_EQ.end();
    string encoded;

    if (success)
    {
        encoded = ENC_ESC_EQ.at(sequence);
    }

    return {success, encoded};
}


pair<bool, string> escape::decode_escape(const std::string& sequence)
{
    bool success = DEC_ESC_EQ.find(sequence) != DEC_ESC_EQ.end();
    string decoded;

    if (success)
    {
        decoded = DEC_ESC_EQ.at(sequence);
    }

    return {success, decoded};
}


const unordered_map<string, string> escape::ENC_ESC_EQ
{
    { "'" , "\\'" },
    { "\"", "\\\""},
    { "=" , "\\=" },
    { "$" , "\\$" },
    { "#" , "\\#" },
    { "\\", "\\\\"},
    { "\a", "\\a" },
    { "\b", "\\b" },
    { "\f", "\\f" },
    { "\n", "\\n" },
    { "\r", "\\r" },
    { "\t", "\\t" },
    { "\v", "\\v" }
};


const unordered_map<string, string> escape::DEC_ESC_EQ
{
    { "\\'" , "'"  },
    { "\\\"", "\"" },
    { "\\=" , "="  },
    { "\\$" , "$"  },
    { "\\#" , "#"  },
    { "\\\\", "\\" },
    { "\\a" , "\a" },
    { "\\b" , "\b" },
    { "\\f" , "\f" },
    { "\\n" , "\n" },
    { "\\r" , "\r" },
    { "\\t" , "\t" },
    { "\\v" , "\v" }
};
