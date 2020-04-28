project(Functions)

set(
    HEADERS
    driver.hh
    parser.hh
    )

BISON_TARGET(
    MyParserWithAst
    parser.y
    ${Functions_SOURCE_DIR}/parser.cpp
    DEFINES_FILE ${Functions_SOURCE_DIR}/parser.hh
)

FLEX_TARGET(
    MyScannerWithAst
    scanner.l
    ${Functions_SOURCE_DIR}/scanner.cpp
)

ADD_FLEX_BISON_DEPENDENCY(MyScannerWithAst MyParserWithAst)

add_executable(
    Functions
    main.cpp
    driver.cpp
    ${BISON_MyParserWithAst_OUTPUTS}
    ${FLEX_MyScannerWithAst_OUTPUTS}

    function-mechanism/Frame.cpp
    function-mechanism/FunctionStorage.cpp
    function-mechanism/FunctionTable.cpp

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
    Classes/Class.cpp

    Declarations/DeclarationList.cpp
    Declarations/VarDecl.cpp
    Declarations/MethodDecl.cpp

    Expression/ExprList.cpp
    Expression/ArrayGetExpression.cpp
    Expression/ArrayRvalueExpression.cpp
    Expression/BinaryCallExpression.cpp
    Expression/BoolExpression.cpp
    Expression/GetLengthExpression.cpp
    Expression/IdentCreateExpression.cpp
    Expression/IdentExpression.cpp
    Expression/InvokeExpression.cpp
    Expression/NotExpression.cpp
    Expression/NumberExpression.cpp
    Expression/ThisExpression.cpp
    Expression/UnarMinusExpression.cpp

    Formals.cpp

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
    Statements/MethodInvokeStatement.cpp
    Statements/OutStatement.cpp
    Statements/ReturnStatement.cpp
    Statements/ScopeDeclStatement.cpp
    Statements/StatementsList.cpp
    Statements/WhileStatement.cpp

    SymbolTable/ScopeLayer.cpp
    SymbolTable/ScopeLayerTree.cpp
    SymbolTable/Symbol.cpp

    Visitors/FunctionCallVisitor.cpp
    Visitors/TemplateVisitor.cpp
    Visitors/TreeBuilder.cpp

    Types/ArrayObject.cpp
    Types/Bool.cpp
    Types/FunctionObject.cpp
    Types/IdentObject.cpp
    Types/Integer.cpp
    Types/UninitObject.cpp

    Location/Location.cpp
)

target_include_directories(
    Functions PRIVATE ${Functions_SOURCE_DIR}
)