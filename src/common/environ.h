#pragma once

/* This header file provides access to all the environment-handling
 * functions through the cstdlib header.
 * 
 * In case they don't exist for a specific system, it declares and
 * defines them with the standard specification for the existing systems
 * for the sake of portability.
*/

#include <cstdlib>
#include <string>
#include <utility>


#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__) || defined(WIN32)
    #define OS_WIN
#endif


#ifdef OS_WIN
int setenv(const char *name, const char *value, int overwrite);
#endif


namespace dotenv
{
    std::pair<bool, std::string> getenv(const std::string& name);

    int setenv(const std::string& name, const std::string& value, bool overwrite);
}


#undef OS_WIN
