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
program:
    main_class classes {$$ = new Program($1, $2); driver.program($$); }

classes:
    %empty {$$ = new Classes(); }
    | class classes { $$ = new Classes($1, $2); }

main_class:
    class "identifier" "{" "public" "static" "void" "main" "(" ")" "{" statements "}"   "}" {$$ = new Main($2, $11); }

classes:
    class "identifier" "{" declarations "}" {$$ = new Class($2, $4); }

declaration:
    variable_declaration {$$ = new VarDecl($1); }
    | method_declaration {$$ = new MethodDecl($1); }

method_declaration:
    "public" type "identifier" "(" argument arguments ")" "{" statements "}" {$$ = new MethodDecl($2, $3, $5, $6, $9); }
    | "public" type "identifier" "(" ")" "{" statements "}" {$$ = new MethodDecl($2, $3, $7); }

arguments:
    %empty {$$ = new Arguments(); }
    | "," variable_decl arguments {$$ = new Arguments($2, $3); }

argument:
    type "identifier" {$$ = new Argument($1, $2); }

variable_declaration:
    type "identifier" ";" {$$ = new VarDecl($1, $2); }

type:
    simple_type {$$ = new SimpleType($1); }
    | array_type {$$ = new ArrayType($1); }

simple_type:
    "int" {$$ = new SimpleType($1); }
    | "boolean" {$$ = new SimpleType($1); }
    | "void" {$$ = new SimpleType($1); }
    | "identifier" {$$ = new SimpleType($1); }

array_type: simple_type> "[" "]" {$$ = ArrayType($1); }

statement:
    "assert" "(" expr ")"  {$$ = new AssertStatement($3); }
    | variable_decl {$$ = new VarDeclStatement($1); }
    | "{" statements "}" {$$ = new StatementsDeclStatement($2); }
    | "if"  "(" expr ")" "{" statement "}" {$$ = new IfStatement($3, $6); }
    | "if"  "(" expr ")" "{" statement "}" "else" "{" statement "}" {$$ = new IfElseStatement($3, $5, $7); }
    | "while"  "(" expr ")" "{" statement "}" {$$ = new WhileStatement($3, $6); }
    |"System.out.println" "(" expr ")" ";" {$$ = new OutStatement($3); }
    | lvalue "=" expr ";" {$$ = new AssignStatement($1, $3); }
    | return expr ";" {$$ = new ReturnStatement($2); }
    | method_invocation ";" {$$ = new MethodInvokeStatement($1); }

method_invocation:
    expr "." "identifier" "(" expr exprs ")" {$$ = new MethodInvoke($1, $3, $5, $6); }
    | expr "." "identifier" "("  ")" {$$ = new MethodInvoke($1, $3); }

lvalue:
    "identifier" {$$ = new SimpleLValue($1); }
    | "identifier" "[" expr "]" {$$ = new ArrayLvalue($1, $3); }

expr:
    expr binary_operator expr
    | <expr> "[" <expr> "]"
    | <expr> "." length
    | new <simple type> "[" <expr> "]"
    | new <type identifier> "(" ")"
    | "!" <expr>
    | "(" <expr> ")"
    | <identifier>
    | <integer literal>
    | this
    | true
    | false
    | method_invocation


<binary operator> ::=	"&&"   |  "||"   |  "<"   | ">"   |  "=="   | "+"   |  "-"   | "*"  | "/"  | "%"


%left "+" "-";
%left "*" "/";
%precedence NEG

exp:
    "number"
    | "identifier" {$$ = driver.variables[$1];}
    | exp "+" exp {$$ = $1 + $3; }
    | exp "-" exp {$$ = $1 - $3; }
    | exp "*" exp {$$ = $1 * $3; }
    | exp "/" exp {$$ = $1 / $3; }
    | "(" exp ")" {$$ = $2; };
    | "-" exp %prec NEG{$$ = -$2; };
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
