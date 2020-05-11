#include "include/driver.hh"
#include "Grammar/parser.hh"

#include "Visitors/FunctionCallVisitor.h"
#include "Visitors/TreeBuilder.h"


#include <Visitors/IrtreeBuildVisitor.h>
#include <irtree/visitors/PrintVisitor.h>

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

    auto func_name = Symbol(program->GetMain()->GetName() + "_____" + "main");

    FunctionCallVisitor function_visitor(
        tree->GetFunctionScopeByName(func_name),
        tree->root_->GetFunc(func_name),
        classes,
        nullptr);

    function_visitor.SetTree(tree);
    function_visitor.Visit(program->GetMain()->GetStatementsList());

    IrtreeBuildVisitor irt_build_visitor(tree, classes);

    irt_build_visitor.Visit(program);

    IrtMapping methods = irt_build_visitor.GetTrees();

    for (auto func_view = methods.begin(); func_view != methods.end(); ++func_view) {
      IRT::PrintVisitor print_visitor_irt( func_view->first + ".txt");
      methods[func_view->first]->Accept(&print_visitor_irt);
    }
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

