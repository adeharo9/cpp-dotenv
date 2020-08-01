#pragma once

/* This header file provides access to all the environment-handling
 * functions through the cstdlib header.
 * 
 * In case they don't exist for a specific system, it declares and
 * defines them with the standard specification for the existing systems
 * for the sake of portability.
*/

#include <cstdlib>


#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__) || defined(WIN32)
    #define OS_WIN
#endif


#ifdef OS_WIN
int setenv(const char *name, const char *value, int overwrite)
{
    int errcode = 0;

    if (overwrite == 0)
    {
        size_t envsize = 0;
        errcode = getenv_s(&envsize, nullptr, 0, name);

        if (errcode != 0 or envsize != 0)
        {
            return errcode;
        }
    }

    return _putenv_s(name, value);
}
#endif


#undef OS_WIN
