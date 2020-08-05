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
        std::string& value();
        const std::string& value() const;

        void set_declared();
        void set_defined();
        void set_value(const std::string& value);

        void add_one_dependency();
        void resolve_one();

    private:

        bool _declared;
        bool _defined;
        bool _local;

        size_t _num_depends;
        std::string _value;

    };


    class SymbolsTable: public std::unordered_map<std::string, SymbolRecord>
    {

    };
}
