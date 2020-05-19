#include "include/driver.hh"
#include "Grammar/parser.hh"

#include "Visitors/FunctionCallVisitor.h"
#include "Visitors/TreeBuilder.h"
#include "irtree/visitors/DoubleCallEliminateVisitor.h"
#include "irtree/visitors/MinusESEQ.h"
#include "irtree/visitors/Linerisation.h"

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
      IRT::PrintVisitor print_visitor_irt(func_view->first + "_old_.txt");
      methods[func_view->first]->Accept(&print_visitor_irt);

      IRT::DoubleCallEliminateVisitor call_eliminate_visitor;
      methods[func_view->first]->Accept(&call_eliminate_visitor);

      auto stmt_result = call_eliminate_visitor.GetTree();

      IRT::PrintVisitor print_visitor_two(func_view->first + "_after_call_elimination_.txt");
      stmt_result->Accept(&print_visitor_two);

      IRT::MinusESEQ minus_eseq1;
      methods[func_view->first]->Accept(&minus_eseq1);
      stmt_result = minus_eseq1.GetTree();
      IRT::MinusESEQ minus_eseq2;
      stmt_result->Accept(&minus_eseq2);
      stmt_result = minus_eseq2.GetTree();


      IRT::Linerisation linerisation;
      methods[func_view->first]->Accept(&linerisation);

      stmt_result = linerisation.GetTree();

      IRT::PrintVisitor print_visitor_four(func_view->first + "_after_all_.txt");
      stmt_result->Accept(&print_visitor_four);
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

