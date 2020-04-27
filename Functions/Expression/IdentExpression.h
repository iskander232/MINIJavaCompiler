#pragma once

#include "Expression.h"

#include <string>

class IdentExpression : public Expression {
 public:
  IdentExpression(std::string name);
  std::string GetName();
  void Accept(Visitor *visitor);
 private:
  std::string name_;
};