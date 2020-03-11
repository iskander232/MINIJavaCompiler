project(NativeInterpreter)


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
    ${NativeInterpreter_SOURCE_DIR}/driver.hh
    ${NativeInterpreter_SOURCE_DIR}/parser.hh
    )

BISON_TARGET(
    NativeInterpreterParser
    parser.y
    ${NativeInterpreter_SOURCE_DIR}/parser.cpp
    DEFINES_FILE ${NativeInterpreter_SOURCE_DIR}/parser.hh
)

FLEX_TARGET(
    NativeInterpreterScanner
    scanner.l
    ${NativeInterpreter_SOURCE_DIR}/scanner.cpp
)

ADD_FLEX_BISON_DEPENDENCY(NativeInterpreterScanner NativeInterpreterParser)

add_executable(
    NativeInterpreter
    main.cpp
    driver.cpp
    ${BISON_NativeInterpreterParser_OUTPUTS}
    ${FLEX_NativeInterpreterScanner_OUTPUTS}
)
target_include_directories(NativeInterpreter PRIVATE ${NativeInterpreter_SOURCE_DIR})



