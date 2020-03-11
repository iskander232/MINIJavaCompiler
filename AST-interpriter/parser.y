%skeleton "lalr1.cc"
%require "3.5"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
    #include <string>
    class Scanner;
    class Driver;
}

// %param { Driver &drv }

%define parse.trace
%define parse.error verbose

%code {
    #include "driver.hh"
    #include "location.hh"

    static yy::parser::symbol_type yylex(Scanner &scanner, Driver& driver) {
        return scanner.ScanToken();
    }
}

%lex-param { Scanner &scanner }
%lex-param { Driver &driver }
%parse-param { Scanner &scanner }
%parse-param { Driver &driver }

%locations

%define api.token.prefix {TOK_}

%token
    END 0 "end of file"
    ASSIGN "="
    MINUS "-"
    PLUS "+"
    STAR "*"
    SLASH "/"
    AND "&&"
    OR "||"
    NOT "!"
    LESS "<"
    MORE ">"
    IS_EQUAL "=="
    PERCENT "%"
    LEFT_ROUND_PAREN "("
    RIGHT_ROUND_PAREN ")"
    LEFT_FIGURE_PAPEN "{"
    RIGHT_FIGURE_PAPEN "}"
    LEFT_SQUARE_PAPEN "["
    RIGHT_SQUARE_PAPEN "]"
    DOT "."
    COMMA ","
    SEMICOLON ";"
    PUBLIC "public"
    STATIC "static"
    VOID "void"
    MAIN "main"
    CLASS "class"
    OUT "out"
    INT "int"
    BOOL "boolean"
    ASSERT "assert"
;

%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"
%nterm <int> exp
%nterm <int> bool_exp

%%
%start program;
program: clases {};

clases:
    %empty {}
    | clases class {};

class:
    "class" "identifier" "{" main_class "}"
main_class:
     "public" "static" "void" "main" "(" ")" "{" statements "}" {};

statements:
    %empty {}
    | statements statement {};


statement:
    "int" "identifier" "=" exp ";" {driver.variables[$2] = $4; }
    |"identifier" "=" exp ";" {driver.variables[$1] = $3; }
    | "boolean" "identifier" "=" bool_exp ";" {driver.variables[$2] = $4; }
    | "identifier" "=" bool_exp ";" {driver.variables[$1] = $3; }
    | "out" "(" exp ")" ";" {
        std::cout << $3 << std::endl;
    }
    | "assert" "(" bool_exp ")" ";" {
        if ($3 == 0){
            throw yy::parser::syntax_error(driver.location, "assert false");

        }
    };


%left "+" "-";
%left "*" "/";

exp:
    "number"
    | "identifier" {$$ = driver.variables[$1];}
    | exp "+" exp {$$ = $1 + $3; }
    | exp "-" exp {$$ = $1 - $3; }
    | exp "*" exp {$$ = $1 * $3; }
    | exp "/" exp {$$ = $1 / $3; }
    | "(" exp ")" {$$ = $2; };
    | "-" exp {$$ = -$2; };
    | exp "%" exp {$$ = $1 % $3; }

bool_exp:
    "number"
    | "identifier" { $$ = driver.variables[$1] & 1; }
    |  exp  {$$ = $1 & 1;}
    | bool_exp "&&" bool_exp {$$ = $1 & $3; }
    | bool_exp "||" bool_exp {$$ = $1 | $3; }
    | "!" bool_exp {$$ = 1 - $2; }
    | exp "<" exp {$$ = $1 < $3 ? 1 : 0; }
    | exp ">" exp {$$ = $1 > $3 ? 1 : 0; }
    | exp "==" exp {$$ = $1 == $3 ? 1 : 0; }

assert:


%%

void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
