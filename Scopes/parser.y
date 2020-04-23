%skeleton "lalr1.cc"
%require "3.5"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
    #include <string>
    #include "forward_declaration.h"

    class Driver;
    class Scanner;
}


%define parse.trace
%define parse.error verbose

%code {
    #include "driver.hh"
    #include "location.hh"
    #include "elements.h"
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
    TRUE "true"
    FALSE "false"
    ASSERT "assert"
    IF "if"
    ELSE "else"
    WHILE "while"
    NEW "new"
    LENGTH "length"
;

%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"

%nterm <ClassesList*> classes
//%nterm <Class*> class
%nterm <Program*> program
%nterm<VarDecl*> declaration
%nterm <VarDecl*> variable_declaration
//%nterm <ExpressionList*> exprs
%nterm <Expression*> expr
%nterm <BinaryOperator*> binary_operator
%nterm <StatementsList*> statements
%nterm <Statement*> statement
%nterm <Lvalue*> lvalue
%nterm <Main*> main_class
%nterm <std::shared_ptr<Object>> simple_type
%nterm <std::shared_ptr<Object>> array_type


%precedence NEG


%left "+" "-";
%left "*" "/";
%left "||";
%left "&&";

%printer { yyo << $$; } <*>;
%%

%start program;

program:  main_class classes {$$ = new Program($1, $2); driver.program = $$; };

classes:
    %empty {$$ = new ClassesList(); }
    ;

main_class:
    "class" "identifier" "{" "public" "static" "void" "main" "(" ")" "{" statements "}"   "}"   {$$ = new Main($2, $11); }
    ;

declaration:
    variable_declaration        {$$ = $1; }
    ;

variable_declaration:
    simple_type "identifier"   {$$ = new VarDecl($1, $2); }
    | array_type "identifier"   {$$ = new VarDecl($1, $2); }
    ;

simple_type:
    "int"                   {$$ = std::dynamic_pointer_cast<Object>(std::make_shared<IntegerObject>(IntegerObject(0)));}
    | "boolean"             {$$ = std::dynamic_pointer_cast<Object>(std::make_shared<BoolObject>(BoolObject(0)));}
    | "identifier"          {$$ = std::dynamic_pointer_cast<Object>(std::make_shared<IdentObject>(IdentObject($1))); }
    ;

array_type:
    simple_type "[" "]"     {$$ = std::dynamic_pointer_cast<Object>(std::make_shared<ArrayObject>(ArrayObject($1))); }
    ;

statements:
    %empty                          {$$ = new StatementsList(); }
    | statements statement          {$1->AddStatement($2); $$ = $1; }
    ;

statement:
    "assert" "(" expr ")" ";"                                               {$$ = new AssertStatement($3); }
    | declaration ";"                                                       {$$ = $1; }
    | "out" "(" expr ")" ";"                                                {$$ = new OutStatement($3); }
    | lvalue "=" expr ";"                                                   {$$ = new AssignStatement($1, $3); }
    | "{" statements "}"                                                    {$$ = new ScopeDeclStatement($2); }
    | "if"  "(" expr ")" "{" statements "}"                                 {$$ = new IfStatement($3, $6); }
    | "if"  "(" expr ")" "{" statements "}" "else" "{" statements "}"       {$$ = new IfElseStatement($3, $6, $10); }
    | "while"  "(" expr ")" "{" statements "}"                              {$$ = new WhileStatement($3, $6); }
    ;

lvalue:
    simple_type "identifier"    {$$ = new SimpleLvalue($1, $2); }
    | array_type "identifier"   {$$ = new ArrayLvalue($1, $2); }
    | "identifier"              {$$ = new Lvalue($1); }
    | "identifier" "[" expr "]" {$$ = new ArrayElementLvalue($1, $3); }
    ;

expr:
    expr binary_operator expr               {$$ = new BinaryCallExpression($1, $2, $3); }
    | "identifier"                          {$$ = new IdentExpression($1); }
    | "number"                              {$$ = new NumberExpression($1); }
    | "-" expr %prec NEG                    {$$ = new UnarMinusExpression($2); }
    | "!" expr                              {$$ = new NotExpression($2); }
    | "(" expr ")"                          {$$ = $2; }
    | "true"                                {$$ = new BoolExpression(true); }
    | "false"                               {$$ = new BoolExpression(false); }
    | expr "[" expr "]"                     {$$ = new ArrayGetExpression($1, $3); }
    | expr "." "length"                     {$$ = new GetLengthExpression($1); }
    | "new" simple_type "[" expr "]"        {$$ = new ArrayRvalueExpression($2, $4); }
    ;

binary_operator:
    "&&"    {$$ = new AndOperator(); }
    | "||"  {$$ = new OrOperator(); }
    | "<"   {$$ = new LessOperator(); }
    | ">"   {$$ = new MoreOperator(); }
    | "=="  {$$ = new EqualOperator(); }
    | "+"   {$$ = new PlusOperator(); }
    | "-"   {$$ = new MinusOperator(); }
    | "*"   {$$ = new MulOperator(); }
    | "/"   {$$ = new DivOperator(); }
    | "%"   {$$ = new ProcOperator(); }
    ;


%%

void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
