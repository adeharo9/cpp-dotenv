#include "dotenv.h"

#include "environ.h"
#include "Parser.h"

#include <fstream>
#include <utility>


using namespace std;
using namespace dotenv;


dotenv::dotenv& dotenv::dotenv::load_dotenv(const string& dotenv_path, const bool overwrite, const bool interpolate)
{
    ifstream env_file;
    env_file.open(dotenv_path);

    if (env_file.good())
    {
        Parser parser;
        parser.parse(env_file, overwrite, interpolate);
        env_file.close();
    }

    return *this;
}


const dotenv::dotenv::value_type dotenv::dotenv::operator[](const key_type& k) const
{
    return getenv(k).second;
}


dotenv::dotenv& dotenv::dotenv::instance()
{
    return _instance;
}


const string dotenv::dotenv::env_filename = ".env";
dotenv::dotenv dotenv::dotenv::_instance;

dotenv::dotenv& dotenv::env = dotenv::instance();
