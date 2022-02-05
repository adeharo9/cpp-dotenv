#pragma once


#include <map>
#include <ostream>
#include <string>
#include <utility>
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


        class position
        {
        public:

            struct less
            {
                bool operator()(const position& p1, const position& p2) const;
            };

        public:

            position(const size_t line, const size_t pos);
            position(const position& position) = default;
            virtual ~position() = default;

            bool operator<(const position& p) const;

        private:

            size_t line;
            size_t pos;

        };

    public:

        logger(bool greedy = false);
        logger(const logger& logger);
        ~logger() = default;

        void fatal(const std::string& msg,
                   const size_t line = 0,
                   const size_t pos = 0);
        void error(const std::string& msg,
                   const size_t line = 0,
                   const size_t pos = 0);
        void warn(const std::string& msg,
                  const size_t line = 0,
                  const size_t pos = 0);
        void info(const std::string& msg,
                  const size_t line = 0,
                  const size_t pos = 0);
        void debug(const std::string& msg,
                   const size_t line = 0,
                   const size_t pos = 0);
        void trace(const std::string& msg,
                   const size_t line = 0,
                   const size_t pos = 0);

        void flush();
        void clear();

    private:

        void place_log(severity severity,
                       const std::string& msg,
                       const size_t line,
                       const size_t pos);
        void flush_severity(severity severity);
        void clear_severity(severity severity);

    private:

        bool _greedy;

        std::multimap<position, std::string, position::less> _fatal;
        std::multimap<position, std::string, position::less> _error;
        std::multimap<position, std::string, position::less> _warn;
        std::multimap<position, std::string, position::less> _info;
        std::multimap<position, std::string, position::less> _debug;
        std::multimap<position, std::string, position::less> _trace;
        const std::vector<std::multimap<position, std::string, position::less>*> _p_severity;

        static const std::string _name;

        static const std::vector<std::string> _severity_lvls;
        static const std::vector<std::ostream*> _out_severity;

    };
}
