project(IR-grammar)
if (CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin")
    execute_process(
            COMMAND brew --prefix bison
            RESULT_VARIABLE BREW_BISON
            OUTPUT_VARIABLE BREW_BISON_PREFIX
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if (BREW_BISON EQUAL 0 AND EXISTS "${BREW_BISON_PREFIX}")
        message(STATUS "Found Bison keg installed by Homebrew at ${BREW_BISON_PREFIX}")
        set(BISON_EXECUTABLE "${BREW_BISON_PREFIX}/bin/bison")
    endif ()

    execute_process(
            COMMAND brew --prefix flex
            RESULT_VARIABLE BREW_FLEX
            OUTPUT_VARIABLE BREW_FLEX_PREFIX
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if (BREW_FLEX EQUAL 0 AND EXISTS "${BREW_FLEX_PREFIX}")
        message(STATUS "Found Flex keg installed by Homebrew at ${BREW_FLEX_PREFIX}")
        set(FLEX_EXECUTABLE "${BREW_FLEX_PREFIX}/bin/flex")
        include_directories(${BREW_FLEX_PREFIX}/include)
    endif ()
endif ()


find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

set(PARSER_TARGET "Parser${PROJECT_NAME}")
set(SCANNER_TARGET "Scanner${PROJECT_NAME}")
set(TREE_TARGET "Tree${PROJECT_NAME}")

set(PARSER_OUTPUT "BISON_${PARSER_TARGET}_OUTPUTS")
set(SCANNER_OUTPUT "FLEX_${SCANNER_TARGET}_OUTPUTS")


set(
        HEADERS
        driver.hh
        parser.hh
)

BISON_TARGET(
        ${PARSER_TARGET}
        parser.y
        ${PROJECT_SOURCE_DIR}/parser.cpp
        COMPILE_FLAGS --graph
        DEFINES_FILE ${PROJECT_SOURCE_DIR}/parser.hh
)

FLEX_TARGET(
        ${SCANNER_TARGET}
        scanner.l
        ${PROJECT_SOURCE_DIR}/scanner.cpp
)



ADD_FLEX_BISON_DEPENDENCY(${SCANNER_TARGET} ${PARSER_TARGET})

set(
        SOURCES
        ${${PARSER_OUTPUT}}
        ${${SCANNER_OUTPUT}}
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



        Types/ArrayObject.cpp
        Types/Bool.cpp
        Types/FunctionObject.cpp
        Types/IdentObject.cpp
        Types/Integer.cpp
        Types/UninitObject.cpp

        Location/Location.cpp
)

add_library(
        ${GRAMMAR_LIB}
        SHARED
        ${SOURCES}
)

target_include_directories(
        ${GRAMMAR_LIB} PRIVATE ${PROJECT_SOURCE_DIR}
)

target_include_directories(
        ${GRAMMAR_LIB} PRIVATE ${PROJECT_SOURCE_DIR}/..
)

target_include_directories(
        ${GRAMMAR_LIB} PRIVATE ${PROJECT_SOURCE_DIR}/../include
)