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
    RETURN "return"
    THIS    "this"
;

%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"


%nterm <std::shared_ptr<Object>> simple_type
%nterm <std::shared_ptr<Object>> array_type
%nterm <BinaryOperator*> binary_operator
%nterm <Class*> class
%nterm <ClassesList*> classes
%nterm <DeclarationList*> declarations
%nterm <Expression*> expr
%nterm <ExprList*> expr_list
%nterm <ExprList*> empty_expr_list
%nterm <ExprList*> some_expr_list
%nterm <Formals*> formals
%nterm <Formals*> empty_formals
%nterm <Formals*> some_formals
%nterm <Lvalue*> lvalue
%nterm <Main*> main_class
%nterm <MethodDecl*> method_declaration
%nterm <Program*> program
%nterm <Statement*> statement
%nterm <StatementsList*> statements
%nterm <Declaration*> declaration
%nterm <VarDecl*> variable_declaration


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
    %empty              {$$ = new ClassesList(); }
    | classes class     {$1->AddClass($2); $$ = $1; }
    ;

class:
    "class" "identifier" "{" declarations "}" {$$ = new Class($2, $4); }
    ;

main_class:
    "class" "identifier" "{" "public" "static" "void" "main" "(" ")" "{" statements "}" "}"   {$$ = new Main($2, $11); }
    ;

declaration:
    variable_declaration        {$$ = $1; }
    | method_declaration        {$$ = $1; }
    ;

declarations:
    %empty                                  {$$ = new DeclarationList(); }
    | declarations declaration              {$1->AddDeclaration($2); $$ = $1; }
    ;

variable_declaration:
    simple_type "identifier" ";"   {$$ = new VarDecl($1, $2); }
    | array_type "identifier" ";"  {$$ = new VarDecl($1, $2); }
    ;

method_declaration:
    "public" simple_type "identifier" "(" formals ")" "{" statements "}"    {$$ = new MethodDecl($2, $3, $5, $8); }
    | "public" array_type "identifier" "(" formals ")" "{" statements "}"   {$$ = new MethodDecl($2, $3, $5, $8); }
    | "public" "void" "identifier" "(" formals ")" "{" statements "}"       { $$ = new MethodDecl(
                    std::dynamic_pointer_cast<Object>(std::make_shared<UninitObject>(UninitObject())), $3, $5, $8);
    }
    ;

formals:
    empty_formals   {$$ = $1; }
    | some_formals  {$$ = $1; }
    ;

empty_formals:
    %empty          {$$ = new Formals(); }
    ;

some_formals:
     simple_type "identifier"                       {$$ = new Formals($1, $2); }
     | array_type "identifier"                      {$$ = new Formals($1, $2); }
     | some_formals "," simple_type "identifier"    {$1->AddFormals($3, $4); $$ = $1; }
     | some_formals "," array_type "identifier"     {$1->AddFormals($3, $4); $$ = $1; }
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
    | "return" expr ";"                                                     {$$ = new ReturnStatement($2); }
    | expr "." "identifier" "(" expr_list ")" ";"                           {$$ = new MethodInvokeStatement($1, $3, $5); }
    ;

lvalue:
    simple_type "identifier"    {$$ = new SimpleLvalue($1, $2); }
    | array_type "identifier"   {$$ = new ArrayLvalue($1, $2); }
    | "identifier"              {$$ = new Lvalue($1); }
    | "identifier" "[" expr "]" {$$ = new ArrayElementLvalue($1, $3); }
    ;

expr_list:
    empty_expr_list         {$$ = $1; }
    | some_expr_list        {$$ = $1; }
    ;

empty_expr_list:
    %empty                  {$$ = new ExprList(); }
    ;

some_expr_list:
    expr                            {$$ = new ExprList($1); }
    | some_expr_list "," expr       {$1->AddExpr($3); $$ = $1; }
    ;

expr:
    expr binary_operator expr                   {$$ = new BinaryCallExpression($1, $2, $3); }
    | "identifier"                              {$$ = new IdentExpression($1); }
    | "number"                                  {$$ = new NumberExpression($1); }
    | "-" expr %prec NEG                        {$$ = new UnarMinusExpression($2); }
    | "!" expr                                  {$$ = new NotExpression($2); }
    | "(" expr ")"                              {$$ = $2; }
    | "true"                                    {$$ = new BoolExpression(true); }
    | "false"                                   {$$ = new BoolExpression(false); }
    | expr "[" expr "]"                         {$$ = new ArrayGetExpression($1, $3); }
    | expr "." "length"                         {$$ = new GetLengthExpression($1); }
    | "new" simple_type "[" expr "]"            {$$ = new ArrayRvalueExpression($2, $4); }
    | "new" "identifier" "(" ")"                {$$ = new IdentCreateExpression($2); }
    | "this"                                    {$$ = new ThisExpression(); }
    | expr "." "identifier" "(" expr_list ")"   {$$ = new InvokeExpression($1, $3, $5); }
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
