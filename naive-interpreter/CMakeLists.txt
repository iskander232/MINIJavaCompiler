project(NativeInterpreter)



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



