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
    #include "Location/Location.h"
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

program:  main_class classes {$$ = new Program($1, $2); driver.program = $$; Location::GetInstance().SetLoc($$, driver.location);};

classes:
    %empty              {$$ = new ClassesList();  Location::GetInstance().SetLoc($$, driver.location);}
    | classes class     {$1->AddClass($2); $$ = $1;  Location::GetInstance().SetLoc($$, driver.location);}
    ;

class:
    "class" "identifier" "{" declarations "}" {$$ = new Class($2, $4);  Location::GetInstance().SetLoc($$, driver.location);}
    ;

main_class:
    "class" "identifier" "{" "public" "static" "void" "main" "(" ")" "{" statements "}" "}"   {$$ = new Main($2, $11);  Location::GetInstance().SetLoc($$, driver.location);}
    ;

declaration:
    variable_declaration        {$$ = $1;  Location::GetInstance().SetLoc($$, driver.location);}
    | method_declaration        {$$ = $1;  Location::GetInstance().SetLoc($$, driver.location);}
    ;

declarations:
    %empty                                  {$$ = new DeclarationList();  Location::GetInstance().SetLoc($$, driver.location);}
    | declarations declaration              {$1->AddDeclaration($2); $$ = $1;  Location::GetInstance().SetLoc($$, driver.location);}
    ;

variable_declaration:
    simple_type "identifier" ";"   {$$ = new VarDecl($1, $2);  Location::GetInstance().SetLoc($$, driver.location);}
    | array_type "identifier" ";"  {$$ = new VarDecl($1, $2);  Location::GetInstance().SetLoc($$, driver.location);}
    ;

method_declaration:
    "public" simple_type "identifier" "(" formals ")" "{" statements "}"    {$$ = new MethodDecl($2, $3, $5, $8);  Location::GetInstance().SetLoc($$, driver.location);}
    | "public" array_type "identifier" "(" formals ")" "{" statements "}"   {$$ = new MethodDecl($2, $3, $5, $8);  Location::GetInstance().SetLoc($$, driver.location);}
    | "public" "void" "identifier" "(" formals ")" "{" statements "}"       { $$ = new MethodDecl(
                    std::dynamic_pointer_cast<Object>(std::make_shared<UninitObject>(UninitObject())), $3, $5, $8);
                                                                               Location::GetInstance().SetLoc($$, driver.location);
    }
    ;

formals:
    empty_formals   {$$ = $1;  Location::GetInstance().SetLoc($$, driver.location);}
    | some_formals  {$$ = $1;  Location::GetInstance().SetLoc($$, driver.location);}
    ;

empty_formals:
    %empty          {$$ = new Formals();  Location::GetInstance().SetLoc($$, driver.location);}
    ;

some_formals:
     simple_type "identifier"                       {$$ = new Formals($1, $2);  Location::GetInstance().SetLoc($$, driver.location);}
     | array_type "identifier"                      {$$ = new Formals($1, $2);  Location::GetInstance().SetLoc($$, driver.location);}
     | some_formals "," simple_type "identifier"    {$1->AddFormals($3, $4); $$ = $1;  Location::GetInstance().SetLoc($$, driver.location);}
     | some_formals "," array_type "identifier"     {$1->AddFormals($3, $4); $$ = $1;  Location::GetInstance().SetLoc($$, driver.location);}
     ;


simple_type:
    "int"                   {$$ = std::dynamic_pointer_cast<Object>(std::make_shared<IntegerObject>(IntegerObject(0)));  }
    | "boolean"             {$$ = std::dynamic_pointer_cast<Object>(std::make_shared<BoolObject>(BoolObject(0)));  }
    | "identifier"          {$$ = std::dynamic_pointer_cast<Object>(std::make_shared<IdentObject>(IdentObject($1)));  }
    ;

array_type:
    simple_type "[" "]"     {$$ = std::dynamic_pointer_cast<Object>(std::make_shared<ArrayObject>(ArrayObject($1))); }
    ;

statements:
    %empty                          {$$ = new StatementsList();  Location::GetInstance().SetLoc($$, driver.location);}
    | statements statement          {$1->AddStatement($2); $$ = $1;  Location::GetInstance().SetLoc($$, driver.location);}
    ;

statement:
    "assert" "(" expr ")" ";"                                               {$$ = new AssertStatement($3);  Location::GetInstance().SetLoc($$, driver.location);}
    | declaration ";"                                                       {$$ = $1;  Location::GetInstance().SetLoc($$, driver.location);}
    | "out" "(" expr ")" ";"                                                {$$ = new OutStatement($3);  Location::GetInstance().SetLoc($$, driver.location);}
    | lvalue "=" expr ";"                                                   {$$ = new AssignStatement($1, $3);  Location::GetInstance().SetLoc($$, driver.location);}
    | "{" statements "}"                                                    {$$ = new ScopeDeclStatement($2);  Location::GetInstance().SetLoc($$, driver.location);}
    | "if"  "(" expr ")" "{" statements "}"                                 {$$ = new IfStatement($3, $6);  Location::GetInstance().SetLoc($$, driver.location);}
    | "if"  "(" expr ")" "{" statements "}" "else" "{" statements "}"       {$$ = new IfElseStatement($3, $6, $10);  Location::GetInstance().SetLoc($$, driver.location);}
    | "while"  "(" expr ")" "{" statements "}"                              {$$ = new WhileStatement($3, $6);  Location::GetInstance().SetLoc($$, driver.location);}
    | "return" expr ";"                                                     {$$ = new ReturnStatement($2);  Location::GetInstance().SetLoc($$, driver.location);}
    | expr "." "identifier" "(" expr_list ")" ";"                           {$$ = new MethodInvokeStatement($1, $3, $5);  Location::GetInstance().SetLoc($$, driver.location);}
    ;

lvalue:
    simple_type "identifier"    {$$ = new SimpleLvalue($1, $2);  Location::GetInstance().SetLoc($$, driver.location);}
    | array_type "identifier"   {$$ = new ArrayLvalue($1, $2);  Location::GetInstance().SetLoc($$, driver.location);}
    | "identifier"              {$$ = new Lvalue($1);  Location::GetInstance().SetLoc($$, driver.location);}
    | "identifier" "[" expr "]" {$$ = new ArrayElementLvalue($1, $3);  Location::GetInstance().SetLoc($$, driver.location);}
    ;

expr_list:
    empty_expr_list         {$$ = $1;  Location::GetInstance().SetLoc($$, driver.location);}
    | some_expr_list        {$$ = $1;  Location::GetInstance().SetLoc($$, driver.location);}
    ;

empty_expr_list:
    %empty                  {$$ = new ExprList();  Location::GetInstance().SetLoc($$, driver.location);}
    ;

some_expr_list:
    expr                            {$$ = new ExprList($1);  Location::GetInstance().SetLoc($$, driver.location);}
    | some_expr_list "," expr       {$1->AddExpr($3); $$ = $1;  Location::GetInstance().SetLoc($$, driver.location);}
    ;

expr:
    expr binary_operator expr                   {$$ = new BinaryCallExpression($1, $2, $3);  Location::GetInstance().SetLoc($$, driver.location);}
    | "identifier"                              {$$ = new IdentExpression($1);  Location::GetInstance().SetLoc($$, driver.location);}
    | "number"                                  {$$ = new NumberExpression($1);  Location::GetInstance().SetLoc($$, driver.location);}
    | "-" expr %prec NEG                        {$$ = new UnarMinusExpression($2);  Location::GetInstance().SetLoc($$, driver.location);}
    | "!" expr                                  {$$ = new NotExpression($2);  Location::GetInstance().SetLoc($$, driver.location);}
    | "(" expr ")"                              {$$ = $2;  Location::GetInstance().SetLoc($$, driver.location);}
    | "true"                                    {$$ = new BoolExpression(true);  Location::GetInstance().SetLoc($$, driver.location);}
    | "false"                                   {$$ = new BoolExpression(false);  Location::GetInstance().SetLoc($$, driver.location);}
    | expr "[" expr "]"                         {$$ = new ArrayGetExpression($1, $3);  Location::GetInstance().SetLoc($$, driver.location);}
    | expr "." "length"                         {$$ = new GetLengthExpression($1);  Location::GetInstance().SetLoc($$, driver.location);}
    | "new" simple_type "[" expr "]"            {$$ = new ArrayRvalueExpression($2, $4);  Location::GetInstance().SetLoc($$, driver.location);}
    | "new" "identifier" "(" ")"                {$$ = new IdentCreateExpression($2);  Location::GetInstance().SetLoc($$, driver.location);}
    | "this"                                    {$$ = new ThisExpression();  Location::GetInstance().SetLoc($$, driver.location);}
    | expr "." "identifier" "(" expr_list ")"   {$$ = new InvokeExpression($1, $3, $5);  Location::GetInstance().SetLoc($$, driver.location);}
    ;

binary_operator:
    "&&"    {$$ = new AndOperator();  Location::GetInstance().SetLoc($$, driver.location);}
    | "||"  {$$ = new OrOperator();  Location::GetInstance().SetLoc($$, driver.location);}
    | "<"   {$$ = new LessOperator();  Location::GetInstance().SetLoc($$, driver.location);}
    | ">"   {$$ = new MoreOperator();  Location::GetInstance().SetLoc($$, driver.location);}
    | "=="  {$$ = new EqualOperator();  Location::GetInstance().SetLoc($$, driver.location);}
    | "+"   {$$ = new PlusOperator();  Location::GetInstance().SetLoc($$, driver.location);}
    | "-"   {$$ = new MinusOperator();  Location::GetInstance().SetLoc($$, driver.location);}
    | "*"   {$$ = new MulOperator();  Location::GetInstance().SetLoc($$, driver.location);}
    | "/"   {$$ = new DivOperator();  Location::GetInstance().SetLoc($$, driver.location);}
    | "%"   {$$ = new ProcOperator();  Location::GetInstance().SetLoc($$, driver.location);}
    ;


%%

void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
