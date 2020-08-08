#pragma once


#include <string>
#include <unordered_map>


namespace dotenv
{
    class ReferenceRecord
    {
    public:

        ReferenceRecord(const size_t line,
                        const size_t pos);
        ReferenceRecord(const ReferenceRecord& reference_record) = default;
        virtual ~ReferenceRecord() = default;

        size_t line() const;
        size_t pos() const;

    private:

        size_t _line;
        size_t _pos;

    };


    class ReferencesTable: public std::unordered_multimap<std::string, ReferenceRecord>
    {

    };
}
