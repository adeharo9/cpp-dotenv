#pragma once


#include <string>


namespace dotenv
{
    class dotenvFacade
    {
    public:

        using   key_type = std::string;
        using value_type = std::string;

    public:

        dotenvFacade& load_dotenv(const std::string& dotenv_path = env_filename,
                            const bool overwrite = false,
                            const bool interpolate = true);

        value_type operator[](const key_type& k) const;

    public:

        virtual ~dotenvFacade() = default;
        dotenvFacade(const dotenvFacade&) = delete;
        void operator=(const dotenvFacade&) = delete;

        static dotenvFacade& instance();
    
    private:

        dotenvFacade() = default;

    private:

        static const std::string env_filename;
        static dotenvFacade _instance;

    };


    extern dotenvFacade& env;
}
