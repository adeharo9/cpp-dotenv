#pragma once


#include <fstream>
#include <string>


namespace dotenv
{
    class dotenv
    {
    public:

        using   key_type = std::string;
        using value_type = std::string;

    public:

        dotenv& load_dotenv(const std::string& dotenv_path = env_filename, const bool overwrite = false, const bool interpolate = true);
        [[deprecated("Replaced by load_dotenv()")]]
        dotenv& config(const std::string& dotenv_path = env_filename, const bool overwrite = false);

        const value_type operator[](const key_type& k) const;

        dotenv(const dotenv&) = delete;
        void operator=(const dotenv&) = delete;

        static dotenv& instance();
    
    private:

        dotenv() = default;

    private:

        static const std::string env_filename;
        static dotenv _instance;

    };


    extern dotenv& env;
}
