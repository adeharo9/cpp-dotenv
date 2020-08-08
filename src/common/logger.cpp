#include "logger.h"

#include <iostream>


using namespace dotenv;
using namespace std;


logger::position::position(const size_t line, const size_t pos):
    line(line),
    pos(pos)
{

}


bool logger::position::operator<(const position& p) const
{
    return this->line < p.line or (this->line == p.line and this->pos < p.pos);
}


bool logger::position::less::operator()(const position& p1, const position& p2)
{
    return p1 < p2;
}


logger::logger(bool greedy):
    _greedy(greedy),
    _fatal(),
    _error(),
    _warn(),
    _info(),
    _debug(),
    _trace(),
    _p_severity
    {
        &_fatal,
        &_error,
        &_warn,
        &_info,
        &_debug,
        &_trace
    }
{

}


logger::logger(const logger& logger):
    _greedy(logger._greedy),
    _fatal(logger._fatal),
    _error(logger._error),
    _warn(logger._warn),
    _info(logger._info),
    _debug(logger._debug),
    _trace(logger._trace),
    _p_severity
    {
        &_fatal,
        &_error,
        &_warn,
        &_info,
        &_debug,
        &_trace
    }
{

}


void logger::fatal(const string& msg, const size_t line, const size_t pos)
{
    place_log(severity::FATAL, msg, line, pos);
}


void logger::error(const string& msg, const size_t line, const size_t pos)
{
    place_log(severity::ERROR, msg, line, pos);
}


void logger::warn(const string& msg, const size_t line, const size_t pos)
{
    place_log(severity::WARN, msg, line, pos);
}


void logger::info(const string& msg, const size_t line, const size_t pos)
{
    place_log(severity::INFO, msg, line, pos);
}


void logger::debug(const string& msg, const size_t line, const size_t pos)
{
    place_log(severity::DEBUG, msg, line, pos);
}


void logger::trace(const string& msg, const size_t line, const size_t pos)
{
    place_log(severity::TRACE, msg, line, pos);
}


void logger::flush()
{
    flush_severity(severity::FATAL);
    flush_severity(severity::ERROR);
    flush_severity(severity::WARN);
    flush_severity(severity::INFO);
    flush_severity(severity::DEBUG);
    flush_severity(severity::TRACE);
}


void logger::clear()
{
    clear_severity(severity::FATAL);
    clear_severity(severity::ERROR);
    clear_severity(severity::WARN);
    clear_severity(severity::INFO);
    clear_severity(severity::DEBUG);
    clear_severity(severity::TRACE);
}


void logger::place_log(severity severity, const string& msg, const size_t line, const size_t pos)
{
    string str = _name + ": " + _severity_lvls.at(severity) + " - " + msg;

    _p_severity.at(severity)->emplace(position{line, pos}, str);

    if (_greedy)
    {
        *_out_severity.at(severity) << str << endl;
    }
}


void logger::flush_severity(severity severity)
{
    ostream& os = *_out_severity.at(severity);
    multimap<position, string, position::less>& container = *_p_severity.at(severity);

    for (const pair<position, string>& element: container)
    {
        os << element.second << endl;
    }

    container.clear();
}


void logger::clear_severity(severity severity)
{
    _p_severity.at(severity)->clear();
}


const string logger::_name = "cpp-dotenv";


const vector<string> logger::_severity_lvls
{
    "FATAL",
    "ERROR",
    "WARN",
    "INFO",
    "DEBUG",
    "TRACE"
};


const vector<ostream*> logger::_out_severity
{
    &cerr,
    &cerr,
    &cerr,
    &cout,
    &clog,
    &clog
};
