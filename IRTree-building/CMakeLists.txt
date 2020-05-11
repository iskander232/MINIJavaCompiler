project(IRT-building)
set(CURRENT_EXECUTABLE "${PROJECT_NAME}Executable")
set(GRAMMAR_LIB "${PROJECT_NAME}GrammarLib")
set(GRAMMAR_PROJECT "${PROJECT_NAME}GrammarProject")
set(IR_LIB "${PROJECT_NAME}IrLib")

set(
        SOURCES
        driver.cpp

        function-mechanism/address/Address.h
        function-mechanism/address/AddressInFrame.h
        function-mechanism/address/AddressInFrame.cpp
        function-mechanism/address/AddressInRegister.h
        function-mechanism/address/AddressInRegister.cpp

        function-mechanism/Frame.h
        function-mechanism/Frame.cpp
        function-mechanism/FrameEmulator.h
        function-mechanism/FrameEmulator.cpp
        function-mechanism/FrameTranslator.h
        function-mechanism/FrameTranslator.cpp
        function-mechanism/FunctionStorage.cpp
        function-mechanism/FunctionTable.cpp



        SymbolTable/ScopeLayer.cpp
        SymbolTable/ScopeLayerTree.cpp
        SymbolTable/Symbol.cpp

        Visitors/FunctionCallVisitor.cpp
        Visitors/IrtreeBuildVisitor.cpp
        Visitors/TemplateVisitor.cpp
        Visitors/TreeBuilder.cpp

)

add_subdirectory(grammar)
add_subdirectory(irtree)

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

target_link_libraries(${CURRENT_EXECUTABLE} ${IR_LIB})

