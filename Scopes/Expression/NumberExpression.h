#pragma once

#include "Expression.h"

#include <memory>

class NumberExpression: public Expression{
 public:
  explicit NumberExpression(int num);
  std::shared_ptr<Object> GetNumber();
  void Accept(Visitor* visitor) override ;
 private:
  std::shared_ptr<IntegerObject> number_;
};