#pragma once

#include <map>
#include <string>
#include <fstream>
#include "Grammar/scanner.h"
#include "Grammar/parser.hh"

#include "Program/Program.h"

class Driver {
 public:
  Driver();
  std::map<std::string, int> variables;
  int result;
  int parse(const std::string &f);
  void Evaluate();
  std::string file;
  bool trace_parsing;

  void scan_begin();
  void scan_end();

  bool trace_scanning;
  yy::location location;

  friend class Scanner;
  Scanner scanner;
  yy::parser parser;
  Program *program;
 private:
  std::ifstream stream;

};
