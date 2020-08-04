#pragma once


#include <string>
#include <unordered_map>


namespace dotenv
{
    class PairsTable: public std::unordered_map<std::string, std::string>
    {

    };
}
