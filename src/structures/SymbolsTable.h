#pragma once


#include <string>
#include <unordered_map>


namespace dotenv
{
    class SymbolRecord
    {
    public:

        SymbolRecord(const bool declared = false,
                     const bool defined = false,
                     const size_t num_depends = 0,
                     const bool local = true);
        SymbolRecord(const SymbolRecord& symbol_record) = default;
        ~SymbolRecord() = default;

        bool complete() const;

        bool declared() const;
        bool defined() const;
        bool resolved() const;
        bool local() const;
        size_t line() const;
        size_t offset() const;
        std::string& value();
        const std::string& value() const;

        void set_declared();
        void set_defined();
        void set_line(const size_t line);
        void set_offset(const size_t offset);
        void set_value(const std::string& value);

        void dependency_add_one();
        void dependency_resolve_one();

    private:

        bool _declared;
        bool _defined;
        bool _local;

        size_t _line;
        size_t _offset;
        size_t _num_depends;
        std::string _value;

    };


    class SymbolsTable: public std::unordered_map<std::string, SymbolRecord>
    {

    };
}
