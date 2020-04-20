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

    Expression/BinaryCallExpression.cpp
    Expression/BoolExpression.cpp
    Expression/IdentExpression.cpp
    Expression/NotExpression.cpp
    Expression/NumberExpression.cpp
    Expression/UnarMinusExpression.cpp

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
    Visitors/PrintVisitor.cpp
    Visitors/TemplateVisitor.cpp
    Visitors/TreeBuilder.cpp

    Types/Object.cpp
    Types/ArrayObject.cpp
    Types/BasicObject.cpp
    Types/IdentObject.cpp
)

target_include_directories(
    Scopes PRIVATE ${Scopes_SOURCE_DIR}
)