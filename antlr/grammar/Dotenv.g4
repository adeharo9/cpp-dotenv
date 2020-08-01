grammar Dotenv;

//////////////////
// Parser rules //
//////////////////

dotenv
    : line (NL line)* EOF
    ;

line
    : WS? pair WS?  # lineContent
    | WS?           # emptyLine
    ;

pair
    : key WS? EQ WS? value
    ;

key
    : (export_token=UNQUOTED_STRING WS)? key_unquoted=UNQUOTED_STRING
    | key_string=STRING
    ;

value
    : UNQUOTED_STRING (WS UNQUOTED_STRING)*
    | STRING
    |
    ;

/////////////////
// Lexer rules //
/////////////////

EQ: '=';
NL: '\r'? '\n';
WS: [ \t]+;

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
