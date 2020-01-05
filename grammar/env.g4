grammar dotenv;

env
    : line_content (NL line_content)* EOF
    ;
// FIRST: SP, UNQUOTED_KEY_CHAR, '"', '\'', CS, NL, EOF
// FOLLOW: -

line_content
    : SP* (key SP* EQ SP* value SP*)? comment?
    ;
// FIRST: SP, UNQUOTED_KEY_CHAR, '"', '\'', CS, 3
// FOLLOW: NL, EOF

key
    : UNQUOTED_KEY | STRING
    ;
// FIRST: UNQUOTED_KEY_CHAR, '"', '\''
// FOLLOW: SP, EQ

value
    : (UNQUOTED_VALUE | STRING)?
    ;
// FIRST: UNQUOTED_VALUE_CHAR, '"', '\'', 3
// FOLLOW: SP, CS, NL, EOF

comment
    : CS UNQUOTED_COMMENT
    ;
// FIRST: CS
// FOLLOW: NL, EOF

STRING
    : '\''SINGLE_UNQUOTED_STRING? '\''
    | '"' DOUBLE_UNQUOTED_STRING? '"'
    ;
// FIRST: '"', '\''
// FOLLOW: SP, EQ, CS, NL, EOF

fragment SINGLE_UNQUOTED_STRING
    : ~[']
    ;

fragment DOUBLE_UNQUOTED_STRING
    : ~["]
    ;

UNQUOTED_KEY
    : UNQUOTED_KEY_CHAR+
    ;
// FIRST: UNQUOTED_KEY_CHAR
// FOLLOW: SP, EQ

fragment UNQUOTED_KEY_CHAR
    : ~[#= "'\t\n\r]
    ;

UNQUOTED_VALUE
    : UNQUOTED_VALUE_CHAR+
    ;
// FIRST: UNQUOTED_VALUE_CHAR
// FOLLOW: SP, CS, NL, EOF

fragment UNQUOTED_VALUE_CHAR
    : ~[# "'\t\n\r]
    ;

UNQUOTED_COMMENT
    : UNQUOTED_COMMENT_CHAR*
    ;
// FIRST: UNQUOTED_COMMENT_CHAR
// FOLLOW: NL, EOF

fragment UNQUOTED_COMMENT_CHAR
    : ~[\n\r]
    ;

CS
    : '#'
    ;

EQ
    : '='
    ;

SP
    : ' '
    | '\t'
    ;

NL
    : '\r'? '\n'
    ;
