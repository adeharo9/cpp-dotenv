#pragma once


#include <cstdlib>
#include <fstream>
#include <stdexcept>
#include <unordered_map>
#include <vector>


#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__) || defined(WIN32)
    #define OS_WIN
#endif

#if defined(_DEBUG) || defined(__DEBUG)
    #include <iostream>

    #define DEBUG_ENTER(x) std::cerr << "ENTER " << row_count << ":" << col_count << " " << #x << std::endl
    #define  DEBUG_EXIT(x) std::cerr << "EXIT  " << row_count << ":" << col_count << " " << #x << std::endl
#else
    #define DEBUG_ENTER(x)
    #define  DEBUG_EXIT(x)
#endif


namespace dotenv
{
    #ifdef OS_WIN
        int setenv(const char* name, const char* value, int overwrite)
        {
            int errcode = 0;

            if (overwrite == 0)
            {
                size_t envsize = 0;
                errcode = getenv_s(&envsize, nullptr, 0, name);

                if (errcode != 0 or envsize != 0)
                {
                    return errcode;
                }
            }

            return _putenv_s(name, value);
        }
    #endif

    class syntax_error: public std::runtime_error
    {
    public:

        syntax_error(const std::string& msg): std::runtime_error(msg) { }

    };


    class container
    {
    private:

        using container_t = std::vector<char>;

    public:

        enum CHAR_MODE
        {
            INCLUDE = 0,
            EXCLUDE = 1
        };

        container() = default;
        container(const container&) = default;
        container(const char c): _include(1, c) { }
        container(std::initializer_list<char> il)
        {
            if (il.size() > 0)
            {
                container_t* c;

                switch (*il.begin())
                {
                    case INCLUDE:
                        c = &_include;
                        break;
                    case EXCLUDE:
                        c = &_exclude;
                        break;
                    default:
                        throw std::runtime_error("");
                }

                c -> insert(c -> end(), il.begin() + 1, il.end());
            }
        }
        ~container() = default;

        inline const container_t& include() const
        {
            return _include;
        }

        inline const container_t& exclude() const
        {
            return _exclude;
        }

        inline container& operator=(const container&) = default;

        inline container operator||(const char c) const
        {
            container cont(*this);
            
            cont._include.emplace_back(c);

            return cont;
        }

        inline container operator||(const container& c) const
        {
            container cont(*this);

            cont._include.insert(cont._include.end(), c._include.begin(), c._include.end());
            cont._exclude.insert(cont._exclude.end(), c._exclude.begin(), c._exclude.end());

            return cont;
        }

    private:

        container_t _include;
        container_t _exclude;

    };


    inline container operator||(const char c, const container cont)
    {
        return cont || c;
    }


    class parser
    {
    public:

        using stream_t = std::istream;

    public:

        parser(stream_t& is, const bool overwrite): overwrite(overwrite), is(is) { }

        inline void parse()
        {
            env();
        }

        inline void init()
        {
            token = is.get();

            row_count = 0;
            col_count = 1;
        }

        inline void env()
        {
            init();

            DEBUG_ENTER(ENV);

            line_content();
            while (token_is(NL_C) or token_is(CR_C))
            {
                NL();
                line_content();
            }
            eof();

            DEBUG_EXIT(ENV);
        }

        inline void line_content()
        {
            ++row_count;
            col_count = 1;

            DEBUG_ENTER(LINE_CONTENT);

            while (token_is(SP)) { match(SP); }

            if (token_is(UNQUOTED_KEY_CHAR || SQ_C || DQ_C))
            {
                key();
                while (token_is(SP)) { match(SP); }
                match(EQ_C);
                while (token_is(SP)) { match(SP); }
                value();
                while (token_is(SP)) { match(SP); }

                register_variable();
            }

            if (token_is(CS_C)) { comment(); }

            DEBUG_EXIT(LINE_CONTENT);
        }

        inline void key()
        {
            DEBUG_ENTER(KEY);

            if (token_is(UNQUOTED_KEY_CHAR))
            {
                bind(_key);
                UNQUOTED_KEY();
                unbind();
            }
            else if (token_is(SQ_C))
            {
                match(SQ_C);
                bind(_key);
                SINGLE_UNQUOTED_STRING();
                unbind();
                match(SQ_C);
            }
            else if (token_is(DQ_C))
            {
                match(DQ_C);
                bind(_key);
                DOUBLE_UNQUOTED_STRING();
                unbind();
                match(DQ_C);
            }
            else { syntax_err(); }

            DEBUG_EXIT(KEY);
        }

        inline void value()
        {
            DEBUG_ENTER(VALUE);

            if (token_is(UNQUOTED_VALUE_CHAR))
            {
                bind(_value);
                UNQUOTED_VALUE();
                unbind();
            }
            else if (token_is(SQ_C))
            {
                match(SQ_C);
                bind(_value);
                SINGLE_UNQUOTED_STRING();
                unbind();
                match(SQ_C);
            }
            else if (token_is(DQ_C))
            {
                match(DQ_C);
                bind(_value);
                DOUBLE_UNQUOTED_STRING();
                unbind();
                match(DQ_C);
            }

            DEBUG_EXIT(VALUE);
        }

        inline void comment()
        {
            DEBUG_ENTER(COMMENT);

            match(CS_C);
            if (token_is(UNQUOTED_COMMENT_CHAR)) { UNQUOTED_COMMENT(); }

            DEBUG_EXIT(COMMENT);
        }

        inline void SINGLE_UNQUOTED_STRING()
        {
            DEBUG_ENTER(SINGLE_UNQUOTED_STRING);
            while (not token_is(SQ_C))
            {
                if (token_is(BS_C))
                {
                    possible_escaped_sequence();
                }
                else
                {
                    next();
                }
            }
            DEBUG_EXIT(SINGLE_UNQUOTED_STRING);
        }

        inline void DOUBLE_UNQUOTED_STRING()
        {
            DEBUG_ENTER(DOUBLE_UNQUOTED_STRING);
            while (not token_is(DQ_C))
            {
                if (token_is(BS_C))
                {
                    possible_escaped_sequence();
                }
                else
                {
                    next();
                }
            }
            DEBUG_EXIT(DOUBLE_UNQUOTED_STRING);
        }

        inline void UNQUOTED_KEY()
        {
            DEBUG_ENTER(UNQUOTED_KEY);
            match(UNQUOTED_KEY_CHAR);
            while (token_is(UNQUOTED_KEY_CHAR)) { match(UNQUOTED_KEY_CHAR); }
            DEBUG_EXIT(UNQUOTED_KEY);
        }

        inline void UNQUOTED_VALUE()
        {
            DEBUG_ENTER(UNQUOTED_VALUE);
            match(UNQUOTED_VALUE_CHAR);
            while (token_is(UNQUOTED_VALUE_CHAR)) { match(UNQUOTED_VALUE_CHAR); }
            DEBUG_EXIT(UNQUOTED_VALUE);
        }

        inline void UNQUOTED_COMMENT()
        {
            DEBUG_ENTER(UNQUOTED_COMMENT);
            match(UNQUOTED_COMMENT_CHAR);
            while (token_is(UNQUOTED_COMMENT_CHAR)) { match(UNQUOTED_COMMENT_CHAR); }
            DEBUG_EXIT(UNQUOTED_COMMENT);
        }

        inline void NL()
        {
            if (token_is(CR_C)) { match(CR_C); }
            match(NL_C);
        }

        inline void possible_escaped_sequence()
        {
            match(BS_C);
            for (auto& equivalence: ESCAPED_EQUIVALENCES)
            {
                if (equivalence.first == token)
                {
                    if (bond and binded != nullptr) { binded -> pop_back(); }
                    else if (bond and binded == nullptr) { throw std::runtime_error("something weird happened to this pointer"); }

                    token = equivalence.second;
                    next();

                    break;
                }
            }
        }

        inline void eof()
        {
            if (not is.eof()) { syntax_err(); }
        }

        inline bool token_is(char c)
        {
            return token == c and not is.eof();
        }

        inline bool token_is(const container& cont)
        {
            if (is.eof()) { return false; }

            for (char c: cont.include())
            {
                if (token == c) { return true; }
            }
            if (cont.exclude().empty()) { return false; }

            for (char c: cont.exclude())
            {
                if (token == c) { return false; }
            }
            return true;
        }

        inline void match(char c)
        {
            if (token_is(c)) { next(); }
            else syntax_err();
        }

        inline void match(const container& c)
        {
            if (token_is(c)) { next(); }
            else syntax_err();
        }

        inline void next()
        {
            if (bond and binded != nullptr) { binded -> append(1, token); }
            else if (bond and binded == nullptr) { throw std::runtime_error("something weird happened to this pointer"); }

            token = is.get();
            ++col_count;
        }

        inline void syntax_err(const std::string& message = "")
        {
            throw syntax_error("Syntax error on line " + std::to_string(row_count) + ":" + std::to_string(col_count) + " -- " + message);
        }

        inline void bind(std::string& s)
        {
            s.clear();
            binded = &s;
            bond = true;
        }

        inline void unbind()
        {
            binded = nullptr;
            bond = false;
        }

        inline void register_variable()
        {
            if (bond or binded != nullptr) { throw std::runtime_error("Something weird is happening"); }
            if (_key.empty()) { throw std::runtime_error(""); }

            setenv(_key.c_str(), _value.c_str(), overwrite ? 1 : 0);
        }

    private:

        bool overwrite = false;

        char token;
        uint row_count;
        uint col_count;

        bool bond = false;
        std::string* binded = nullptr;

        std::string _key;
        std::string _value;

        stream_t& is;

    private:

        static const char CS_C = '#';   // Comment (sharp)
        static const char EQ_C = '=';   // Equal sign
        static const char SP_C = ' ';   // Space
        static const char SQ_C = '\'';  // Single quote
        static const char DQ_C = '\"';  // Double quote
        static const char TB_C = '\t';  // Tabulator
        static const char NL_C = '\n';  // Newline
        static const char CR_C = '\r';  // Carriage return
        static const char BS_C = '\\';  // Backslash
        static const container SP;
        static const container UNQUOTED_KEY_CHAR;
        static const container UNQUOTED_VALUE_CHAR;
        static const container UNQUOTED_COMMENT_CHAR;
        static const std::vector<std::pair<char, char>> ESCAPED_EQUIVALENCES;

    };


    const container parser::SP
    {
        container::CHAR_MODE::INCLUDE,
        SP_C,
        TB_C
    };


    const container parser::UNQUOTED_KEY_CHAR
    {
        container::CHAR_MODE::EXCLUDE,
        CS_C,
        EQ_C,
        SP_C,
        SQ_C,
        DQ_C,
        TB_C,
        NL_C,
        CR_C
    };


    const container parser::UNQUOTED_VALUE_CHAR
    {
        container::CHAR_MODE::EXCLUDE,
        CS_C,
        SP_C,
        SQ_C,
        DQ_C,
        TB_C,
        NL_C,
        CR_C
    };


    const container parser::UNQUOTED_COMMENT_CHAR
    {
        container::CHAR_MODE::EXCLUDE,
        NL_C,
        CR_C
    };

    const std::vector<std::pair<char, char>> parser::ESCAPED_EQUIVALENCES
    {
        { '?' , '?'  },
        { '\'', '\'' },
        { '"' , '"'  },
        { '\\', '\\' },
        { 'a' , '\a' },
        { 'b' , '\b' },
        { 'f' , '\f' },
        { 'n' , '\n' },
        { 'r' , '\r' },
        { 't' , '\t' },
        { 'v' , '\v' }
    };

    class dotenv
    {
    private:

        using   key_type = std::string;
        using value_type = std::string;

    public:

        inline dotenv& load_dotenv(const std::string& dotenv_path = env_filename, const bool overwrite = false)
        {
            std::ifstream env_file;
            env_file.open(dotenv_path);

            if (env_file.good())
            {
                parse(env_file, overwrite);
                env_file.close();
            }

            return *this;
        }

        [[deprecated("Replaced by load_dotenv()")]]
        inline dotenv& config(const std::string& dotenv_path = env_filename)
        {
            return load_dotenv(dotenv_path);
        }

        inline const value_type operator[](const key_type& k) const
        {
            const char* value = std::getenv(k.c_str());
            
            if (value == nullptr)
            {
                value = "";
            }

            return value_type(value);
        }

        dotenv(const dotenv&) = delete;
        void operator=(const dotenv&) = delete;

        static dotenv& instance()
        {
            return _instance;
        }
    
    private:

        dotenv() = default;

        inline void parse(std::ifstream& file, const bool overwrite = false)
        {
            parser parser(file, overwrite);
            parser.parse();
        }

    private:

        bool _config = false;

        static const std::string env_filename;
        static dotenv _instance;

    };


    const std::string dotenv::env_filename = ".env";
    dotenv dotenv::_instance;


    dotenv& env = dotenv::instance().load_dotenv();
}
