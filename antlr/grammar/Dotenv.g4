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
    | (export_token=UNQUOTED_STRING WS)? key_string=STRING
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
    : '\'' SINGLE_UNQUOTED_STRING '\''
    | '"' DOUBLE_UNQUOTED_STRING '"'
    ;

UNQUOTED_STRING: (ESC_SEQ | ~[#="' \t\r\n\\])+;

fragment COMMENT_STRING: ~[\r\n]+;

fragment SINGLE_UNQUOTED_STRING: (ESC_SEQ | ~['\\])*;
fragment DOUBLE_UNQUOTED_STRING: (ESC_SEQ | ~["\\])*;

fragment ESC_SEQ
    : '\\' ('\''|'"'|'='|'$'|'#'|'\\'|'a'|'b'|'f'|'n'|'r'|'t'|'v')
    | UNICODE_ESC
    | OCTAL_ESC
    ;
fragment OCTAL_ESC
    : '\\' ('0'..'3') ('0'..'7') ('0'..'7')
    | '\\' ('0'..'7') ('0'..'7')
    | '\\' ('0'..'7')
    ;
fragment UNICODE_ESC
    : '\\' 'u' HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT
    ;
fragment HEX_DIGIT: ('0'..'9'|'a'..'f'|'A'..'F');
