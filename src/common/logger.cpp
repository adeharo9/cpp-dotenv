#include "logger.h"

#include <iostream>


using namespace dotenv;
using namespace std;


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


void logger::fatal(const string& msg)
{
    place_log(severity::FATAL, msg);
}


void logger::error(const string& msg)
{
    place_log(severity::ERROR, msg);
}


void logger::warn(const string& msg)
{
    place_log(severity::WARN, msg);
}


void logger::info(const string& msg)
{
    place_log(severity::INFO, msg);
}


void logger::debug(const string& msg)
{
    place_log(severity::DEBUG, msg);
}


void logger::trace(const string& msg)
{
    place_log(severity::TRACE, msg);
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


void logger::place_log(severity severity, const string& msg)
{
    string str = _name + ": " + _severity_lvls.at(severity) + " - " + msg;

    _p_severity.at(severity)->emplace_back(str);

    if (_greedy)
    {
        *_out_severity.at(severity) << str << endl;
    }
}


void logger::flush_severity(severity severity)
{
    ostream& os = *_out_severity.at(severity);
    vector<string>& container = *_p_severity.at(severity);

    for (const string& msg: container)
    {
        os << msg << endl;
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
