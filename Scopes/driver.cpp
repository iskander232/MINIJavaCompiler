#include "driver.hh"
#include "parser.hh"

#include "Visitors/Interpreter.h"
#include "Visitors/TreeBuilder.h"

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
  TreeBuilder tree_builder;
  tree_builder.Visit(program);
  ScopeLayerTree* tree = tree_builder.GetTree();
  tree->ResetVisit();
  Interpreter interpreter(tree);
  interpreter.Visit(program);
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

