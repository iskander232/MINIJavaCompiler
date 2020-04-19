#pragma once

#include "Statements/Statement.h"

#include <string>

class VarDecl: public Statement{
 public:
  VarDecl(std::string name);
  std::string GetName();
  void Accept(Visitor* visitor) override ;
 private:
  std::string name_;
};