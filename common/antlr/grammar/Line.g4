grammar Line;

//////////////////
// Parser rules //
//////////////////

line
    : content? EOF
    ;

content
    : (STRING_CHAR | ESC_SEQ | variable)+
    ;

variable
    : BOUNDED_VARIABLE
    | UNBOUNDED_VARIABLE
    ;

/////////////////
// Lexer rules //
/////////////////

ESC_SEQ
    : '\\' ('\''|'"'|'='|'$'|'#'|'\\'|'a'|'b'|'f'|'n'|'r'|'t'|'v')
    | UNICODE_ESC
    | OCTAL_ESC
    ;

BOUNDED_VARIABLE: '$' '{' UNBOUNDED_STRING '}';
UNBOUNDED_VARIABLE: '$' LIMITED_UNBOUNDED_STRING;

STRING_CHAR: .;

fragment UNICODE_ESC
    : '\\' 'u' HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT
    ;
fragment OCTAL_ESC
    : '\\' ('0'..'3') ('0'..'7') ('0'..'7')
    | '\\' ('0'..'7') ('0'..'7')
    | '\\' ('0'..'7')
    ;
fragment UNBOUNDED_STRING: ~[{}]+;
fragment LIMITED_UNBOUNDED_STRING: ('_' | LETTER) ('_' | LETTER | DIGIT)*;
fragment LETTER: 'a'..'z' | 'A'..'Z';
fragment DIGIT: '0'..'9';
fragment HEX_DIGIT: ('0'..'9'|'a'..'f'|'A'..'F');
