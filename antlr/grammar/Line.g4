grammar Line;

//////////////////
// Parser rules //
//////////////////

line
    : content? EOF
    ;

content
    : (STRING_CHAR | ESC_USD | variable)+
    ;

variable
    : BOUNDED_VARIABLE
    | UNBOUNDED_VARIABLE
    ;

/////////////////
// Lexer rules //
/////////////////

ESC_USD: '\\' '$';

BOUNDED_VARIABLE: '$' '{' UNBOUNDED_STRING '}';
UNBOUNDED_VARIABLE: '$' LIMITED_UNBOUNDED_STRING;

STRING_CHAR: .;

fragment UNBOUNDED_STRING: ~[{}]+;
fragment LIMITED_UNBOUNDED_STRING: LETTER (LETTER | DIGIT)*;
fragment LETTER: 'a'..'z' | 'A'..'Z';
fragment DIGIT: '0'..'9';
