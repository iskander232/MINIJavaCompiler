#include "driver.hh"
#include "parser.hh"

#include "Visitors/FunctionCallVisitor.h"
#include "Visitors/TreeBuilder.h"

#include <function-mechanism/FunctionStorage.h>
#include <Location/Location.h>

Driver::Driver() :
    trace_parsing(false),
    trace_scanning(false),
    scanner(*this), parser(scanner, *this) {}

int Driver::parse(const std::string &f) {
  file = f;
  location.initialize(&file);
  scan_begin();
  parser.set_debug_level(trace_parsing);
  int res = parser();
  scan_end();
  return res;
}

void Driver::Evaluate() {
  try {
    TreeBuilder tree_builder;
    tree_builder.Visit(program);
    ScopeLayerTree *tree = tree_builder.GetTree();
    auto functions = tree_builder.GetFunctions();
    auto classes = tree_builder.GetClasses();

    FunctionStorage &storage = FunctionStorage::GetInstance();
    for (auto it : functions) {
      storage.Set(it.first, it.second);
    }
    auto func_name = std::make_pair(Symbol(program->GetMain()->GetName()), Symbol("main"));

    FunctionCallVisitor function_visitor(
        tree->GetFunctionScopeByName(func_name),
        tree->root_->GetFunc(func_name),
        classes,
        nullptr);

    function_visitor.SetTree(tree);
    function_visitor.Visit(program->GetMain()->GetStatementsList());
  } catch (const std::runtime_error &e) {
    std::cerr << Location::GetInstance().LastLoc() << " : " << e.what();
  }
}

void Driver::scan_begin() {
  scanner.set_debug(trace_scanning);
  if (file.empty() || file == "-") {
  } else {
    stream.open(file);
    scanner.yyrestart(&stream);
  }
}

void Driver::scan_end() {
  stream.close();
}

