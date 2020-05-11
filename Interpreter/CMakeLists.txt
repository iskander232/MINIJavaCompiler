project(Interpreter)
set(CURRENT_EXECUTABLE "${PROJECT_NAME}Executable")
set(GRAMMAR_LIB "${PROJECT_NAME}GrammarLib")
set(GRAMMAR_PROJECT "${PROJECT_NAME}GrammarProject")

set(
        SOURCES
        driver.cpp
        ../IRTree-building/function-mechanism/Frame.cpp
        function-mechanism/FunctionStorage.cpp
        function-mechanism/FunctionTable.cpp



        SymbolTable/ScopeLayer.cpp
        SymbolTable/ScopeLayerTree.cpp
        SymbolTable/Symbol.cpp

        Visitors/FunctionCallVisitor.cpp
        Visitors/TemplateVisitor.cpp
        Visitors/TreeBuilder.cpp

)

add_subdirectory(grammar)

add_executable(
        ${CURRENT_EXECUTABLE}
        main.cpp
        ${SOURCES}
)


target_include_directories(
        ${CURRENT_EXECUTABLE} PRIVATE ${PROJECT_SOURCE_DIR}
)
target_include_directories(
        ${CURRENT_EXECUTABLE} PRIVATE ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/grammar
)


target_link_libraries(${CURRENT_EXECUTABLE} ${GRAMMAR_LIB})
