#pragma once


#include <ostream>
#include <string>
#include <vector>


namespace dotenv
{
    class logger
    {
    private:

        enum severity
        {
            FATAL = 0,
            ERROR = 1,
            WARN  = 2,
            INFO  = 3,
            DEBUG = 4,
            TRACE = 5
        };

    public:

        logger(bool greedy = false);
        logger(const logger& logger);
        ~logger() = default;

        void fatal(const std::string& msg);
        void error(const std::string& msg);
        void warn(const std::string& msg);
        void info(const std::string& msg);
        void debug(const std::string& msg);
        void trace(const std::string& msg);

        void flush();
        void clear();

    private:

        void place_log(severity severity, const std::string& msg);
        void flush_severity(severity severity);
        void clear_severity(severity severity);

    private:

        bool _greedy;

        std::vector<std::string> _fatal;
        std::vector<std::string> _error;
        std::vector<std::string> _warn;
        std::vector<std::string> _info;
        std::vector<std::string> _debug;
        std::vector<std::string> _trace;
        const std::vector<std::vector<std::string>*> _p_severity;

        static const std::string _name;

        static const std::vector<std::string> _severity_lvls;
        static const std::vector<std::ostream*> _out_severity;

    };
}
