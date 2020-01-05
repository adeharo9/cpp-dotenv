#pragma once


#include <fstream>
#include <stdexcept>
#include <unordered_map>
#include <vector>


#ifdef _DEBUG
    #include <iostream>

    #define DEBUG_ENTER(x) std::cerr << "ENTER " << row_count << ":" << col_count << " " << #x << std::endl
    #define  DEBUG_EXIT(x) std::cerr << "EXIT  " << row_count << ":" << col_count << " " << #x << std::endl
#else
    #define DEBUG_ENTER(x)
    #define  DEBUG_EXIT(x)
#endif


namespace dotenv
{
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

        using mapped_t = std::string;
        using  value_t = std::string;
        using stream_t = std::istream;
        using    map_t = std::unordered_map<mapped_t, value_t>;

    public:

        parser(stream_t& is, map_t& map): is(is), map(map) { }

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

                insert_to_map();
            }

            if (token_is(CS_C)) { comment(); }

            DEBUG_EXIT(LINE_CONTENT);
        }

        inline void key()
        {
            DEBUG_ENTER(KEY);
            bind(_key);

            if (token_is(UNQUOTED_KEY_CHAR)) { UNQUOTED_KEY(); }
            else if (token_is(SQ_C) or token_is(DQ_C)) { STRING(); }
            else { syntax_err(); }

            unbind(_key);
            DEBUG_EXIT(KEY);
        }

        inline void value()
        {
            DEBUG_ENTER(VALUE);
            bind(_value);

            if (token_is(UNQUOTED_VALUE_CHAR)) { UNQUOTED_VALUE(); }
            else if (token_is(SQ_C) or token_is(DQ_C)) { STRING(); }

            unbind(_value);
            DEBUG_EXIT(VALUE);
        }

        inline void comment()
        {
            DEBUG_ENTER(COMMENT);

            match(CS_C);
            if (token_is(UNQUOTED_COMMENT_CHAR)) { UNQUOTED_COMMENT(); }

            DEBUG_EXIT(COMMENT);
        }

        inline void STRING()
        {
            DEBUG_ENTER(STRING);

            if (token_is(SQ_C))
            {
                match(SQ_C);
                while (not token_is(SQ_C)) { next(); }
                match(SQ_C);
            }
            else if (token_is(DQ_C))
            {
                match(DQ_C);
                while (not token_is(DQ_C)) { next(); }
                match(DQ_C);
            }
            else { syntax_err(); }

            DEBUG_EXIT(STRING);
        }

        inline void UNQUOTED_KEY()
        {
            match(UNQUOTED_KEY_CHAR);
            while (token_is(UNQUOTED_KEY_CHAR)) { match(UNQUOTED_KEY_CHAR); }
        }

        inline void UNQUOTED_VALUE()
        {
            match(UNQUOTED_VALUE_CHAR);
            while (token_is(UNQUOTED_VALUE_CHAR)) { match(UNQUOTED_VALUE_CHAR); }
        }

        inline void UNQUOTED_COMMENT()
        {
            match(UNQUOTED_COMMENT_CHAR);
            while (token_is(UNQUOTED_COMMENT_CHAR)) { match(UNQUOTED_COMMENT_CHAR); }
        }

        inline void NL()
        {
            if (token_is(CR_C)) { match(CR_C); }
            match(NL_C);
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

        inline void syntax_err()
        {
            throw syntax_error("Syntax error on line " + std::to_string(row_count) + ":" + std::to_string(col_count));
        }

        inline void bind(std::string& s)
        {
            s.clear();
            binded = &s;
            bond = true;
        }

        inline void unbind(std::string& s)
        {
            binded = nullptr;
            bond = false;
        }

        inline void insert_to_map()
        {
            if (bond or binded != nullptr) { throw std::runtime_error("Something weird is happening"); }
            if (_key.empty()) { throw std::runtime_error(""); }

            map.emplace(_key, _value);
        }

    private:

        char token;
        uint row_count;
        uint col_count;

        bool bond = false;
        std::string* binded = nullptr;

        std::string _key;
        std::string _value;

        stream_t& is;
        map_t& map;

    private:

        static const char CS_C = '#';
        static const char EQ_C = '=';
        static const char SP_C = ' ';
        static const char SQ_C = '\'';
        static const char DQ_C = '\"';
        static const char TB_C = '\t';
        static const char NL_C = '\n';
        static const char CR_C = '\r';
        static const container SP;
        static const container UNQUOTED_KEY_CHAR;
        static const container UNQUOTED_VALUE_CHAR;
        static const container UNQUOTED_COMMENT_CHAR;

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


    class dotenv
    {
    private:

        using   key_type = std::string;
        using value_type = std::string;

    public:

        inline dotenv& config(const std::string& full_path = env_filename)
        {
            std::ifstream env_file;
            env_file.open(full_path);

            if (env_file.good())
            {
                parse(env_file);
                env_file.close();
            }

            _config = true;

            return *this;
        }

        inline const value_type& operator[](const key_type& k) const
        {
            if (not _config) { throw std::logic_error(config_err); }

            try
            {
                return _env.at(k);
            }
            catch (const std::out_of_range& exception)
            {
                throw std::out_of_range("key '" + k + "' not found");
            }
        }

        dotenv(const dotenv&) = delete;
        void operator=(const dotenv&) = delete;

        static dotenv& instance()
        {
            return _instance;
        }
    
    private:

        dotenv() = default;

        inline void parse(std::ifstream& file)
        {
            parser parser(file, _env);
            parser.parse();
        }

    private:

        bool _config = false;
        std::unordered_map<key_type, value_type> _env;

        static const std::string env_filename;
        static const std::string config_err;
        static dotenv _instance;

    };


    const std::string dotenv::env_filename = ".env";
    const std::string dotenv::config_err = "config() method must be called first";
    dotenv dotenv::_instance;


    dotenv& env = dotenv::instance().config();
}
