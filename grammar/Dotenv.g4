grammar Dotenv;

//////////////////
// Parser rules //
//////////////////

dotenv
    : line_content (NL line_content)* EOF
    ;

line_content
    : kv_pair
    |
    ;

kv_pair
    : key EQ value
    ;

key
    : UNQUOTED_STRING
    | STRING
    ;

value
    : UNQUOTED_STRING
    | STRING
    |
    ;

/////////////////
// Lexer rules //
/////////////////

EQ: '=';
NL: '\r'? '\n';
WS: [ \t]+ -> skip;
EXPORT: 'export' -> skip;

COMMENT
    : '#' COMMENT_STRING? -> skip
    ;

STRING
    : '\''SINGLE_UNQUOTED_STRING? '\''
    | '"' DOUBLE_UNQUOTED_STRING? '"'
    ;

UNQUOTED_STRING: ~[#="' \t\r\n]+;

fragment COMMENT_STRING: ~[\r\n]+;
fragment SINGLE_UNQUOTED_STRING: ~[']+;
fragment DOUBLE_UNQUOTED_STRING: ~["]+;
