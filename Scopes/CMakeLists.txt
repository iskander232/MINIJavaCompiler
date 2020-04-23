project(Scopes)

set(
    HEADERS
    driver.hh
    parser.hh
    )

BISON_TARGET(
    MyParserWithAst
    parser.y
    ${Scopes_SOURCE_DIR}/parser.cpp
    DEFINES_FILE ${Scopes_SOURCE_DIR}/parser.hh
)

FLEX_TARGET(
    MyScannerWithAst
    scanner.l
    ${Scopes_SOURCE_DIR}/scanner.cpp
)

ADD_FLEX_BISON_DEPENDENCY(MyScannerWithAst MyParserWithAst)

add_executable(
    Scopes
    main.cpp
    driver.cpp
    ${BISON_MyParserWithAst_OUTPUTS}
    ${FLEX_MyScannerWithAst_OUTPUTS}

    BinaryOperator/AndOperator.cpp
    BinaryOperator/DivOperator.cpp
    BinaryOperator/EqualOperator.cpp
    BinaryOperator/LessOperator.cpp
    BinaryOperator/MinusOperator.cpp
    BinaryOperator/MoreOperator.cpp
    BinaryOperator/MulOperator.cpp
    BinaryOperator/OrOperator.cpp
    BinaryOperator/PlusOperator.cpp
    BinaryOperator/ProcOperator.cpp

    Classes/ClassesList.cpp

    Declarations/VarDecl.cpp

    Expression/ArrayGetExpression.cpp
    Expression/ArrayRvalueExpression.cpp
    Expression/BinaryCallExpression.cpp
    Expression/BoolExpression.cpp
    Expression/GetLengthExpression.cpp
    Expression/IdentExpression.cpp
    Expression/NotExpression.cpp
    Expression/NumberExpression.cpp
    Expression/UnarMinusExpression.cpp

    Lvalue/Lvalue.cpp
    Lvalue/ArrayElementLvalue.cpp
    Lvalue/ArrayLvalue.cpp
    Lvalue/SimpleLvalue.cpp

    Main/Main.cpp

    Program/Program.cpp

    Statements/AssertStatement.cpp
    Statements/AssignStatement.cpp
    Statements/IfElseStatement.cpp
    Statements/IfStatement.cpp
    Statements/OutStatement.cpp
    Statements/ScopeDeclStatement.cpp
    Statements/StatementsList.cpp
    Statements/WhileStatement.cpp

    SymbolTable/ScopeLayer.cpp
    SymbolTable/ScopeLayerTree.cpp
    SymbolTable/Symbol.cpp

    Visitors/Interpreter.cpp
    Visitors/TemplateVisitor.cpp
    Visitors/TreeBuilder.cpp

    Types/ArrayObject.cpp
    Types/Bool.cpp
    Types/IdentObject.cpp
    Types/Integer.cpp
    Types/SimpleObject.cpp
    Types/UninitObject.cpp
)

target_include_directories(
    Scopes PRIVATE ${Scopes_SOURCE_DIR}
)