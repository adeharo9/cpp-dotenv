grammar dotenv;

//////////////////
// Parser rules //
//////////////////

dotenv
    : line_content (NL line_content)* EOF
    ;

line_content
    : kv_pair? COMMENT?
    ;

kv_pair
    : key EQ value?
    ;

key
    : UNQUOTED_KEY
    | STRING
    ;

value
    : UNQUOTED_VALUE
    | STRING
    ;

/////////////////
// Lexer rules //
/////////////////

COMMENT
    : '#' COMMENT_STRING? -> skip
    ;

STRING
    : '\''SINGLE_UNQUOTED_STRING? '\''
    | '"' DOUBLE_UNQUOTED_STRING? '"'
    ;

UNQUOTED_KEY: ~[#="' \t\n\r]+;
UNQUOTED_VALUE: ~[#"' \t\n\r]+;

EQ: '=';
NL: '\r'? '\n' -> skip;
WS: [ \t\r\n]+ -> skip;

fragment COMMENT_STRING: ~[\r\n]+;
fragment SINGLE_UNQUOTED_STRING: ~[']+;
fragment DOUBLE_UNQUOTED_STRING: ~["]+;
