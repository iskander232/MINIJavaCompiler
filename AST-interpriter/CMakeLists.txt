project(Interpreter)


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

set(
    HEADERS
    ${Interpreter_SOURCE_DIR}/driver.hh
    ${Interpreter_SOURCE_DIR}/parser.hh
    )

BISON_TARGET(
    InterpreterParser
    parser.y
    ${Interpreter_SOURCE_DIR}/parser.cpp
    DEFINES_FILE ${Interpreter_SOURCE_DIR}/parser.hh
)

FLEX_TARGET(
    InterpreterScanner
    scanner.l
    ${Interpreter_SOURCE_DIR}/scanner.cpp
)

ADD_FLEX_BISON_DEPENDENCY(InterpreterScanner InterpreterParser)

add_executable(
    Interpreter
    main.cpp
    driver.cpp
    ${BISON_InterpreterParser_OUTPUTS}
    ${FLEX_InterpreterScanner_OUTPUTS}
)
target_include_directories(Interpreter PRIVATE ${Interpreter_SOURCE_DIR})



