#include "dotenv.h"

#include "environ.h"
#include "Parser.h"

#include <fstream>


using namespace std;
using namespace dotenv;


dotenv::dotenv& dotenv::dotenv::load_dotenv(const string& dotenv_path, const bool overwrite)
{
    ifstream env_file;
    env_file.open(dotenv_path);

    if (env_file.good())
    {
        parse(env_file, overwrite);
        env_file.close();
    }

    return *this;
}


dotenv::dotenv& dotenv::dotenv::config(const string& dotenv_path, const bool overwrite)
{
    return load_dotenv(dotenv_path);
}


const dotenv::dotenv::value_type dotenv::dotenv::operator[](const key_type& k) const
{
    const char* value = getenv(k.c_str());
    
    if (value == nullptr)
    {
        value = "";
    }

    return value_type(value);
}


dotenv::dotenv& dotenv::dotenv::instance()
{
    return _instance;
}


void dotenv::dotenv::parse(ifstream& file, const bool overwrite)
{
    Parser parser(file, overwrite);
    parser.parse();
}


const string dotenv::dotenv::env_filename = ".env";
dotenv::dotenv dotenv::dotenv::_instance;

dotenv::dotenv& dotenv::env = dotenv::instance();
